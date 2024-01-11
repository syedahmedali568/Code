import tkinter as tk
from tkinter import ttk, messagebox
from ttkthemes import ThemedStyle
import requests
import time
import random
import matplotlib.pyplot as plt

class PriorityQueue:
    def __init__(self): 
        self.queue = []

    def push(self, item): 
        self.queue.append(item)
        self.queue.sort()

    def pop(self):
        if not self.is_empty():
            return self.queue.pop(0)

    def is_empty(self):
        return len(self.queue) == 0

class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, node, neighbor):
        if node not in self.graph:
            self.graph[node] = []
        self.graph[node].append(neighbor)

    def get_neighbors(self, node):
        return self.graph.get(node, [])

class WeatherApp:
    def __init__(self, root):
        self.root = root
        self.root.geometry("800x600")
        self.root.title("Weather App")

        self.style = ThemedStyle(self.root)
        self.style.set_theme("arc")

        self.weather_cache = {}
        self.cities_list = []
        self.priority_queue = PriorityQueue()
        self.weather_graph = Graph()
        self.city_list = self.load_city_list()

        self.show_welcome_message()

    def load_city_list(self):
        with open('Cities.txt', 'r') as file:
            return [line.strip() for line in file]

    def correct_city_typo(self, typo_city):
        closest_match = min(self.city_list, key=lambda city: self.levenshtein_distance(typo_city, city))
        corrected_city = messagebox.askquestion(
            "City Correction",
            f"Did you mean {closest_match} instead of {typo_city}?"
        )

        if corrected_city == "yes":
            return closest_match
        else:
            return typo_city

    @staticmethod
    def levenshtein_distance(s1, s2):
        if len(s1) < len(s2):
            return WeatherApp.levenshtein_distance(s2, s1)

        if len(s2) == 0:
            return len(s1)

        previous_row = range(len(s2) + 1)
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            for j, c2 in enumerate(s2):
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                current_row.append(min(insertions, deletions, substitutions))

            previous_row = current_row

        return previous_row[-1]

    def show_welcome_message(self):
        welcome_label = ttk.Label(self.root, text="Welcome to the PyPro Weather App", font=("poppins", 18, "bold"))
        welcome_label.pack(pady=20)

        loading_label = ttk.Label(self.root, text="Loading...", font=("poppins", 14))
        loading_label.pack()

        self.root.after(3000, self.show_main_interface)

    def show_main_interface(self):
        for widget in self.root.winfo_children():
            widget.destroy()

        self.root.configure(bg='turquoise')

        title_font = ("poppins", 35, "bold")
        info_font = ("poppins", 15, "bold")

        self.textField = ttk.Entry(self.root, justify='center', font=title_font)
        self.textField.pack(pady=20)
        self.textField.focus()
        self.textField.bind('<Return>', self.get_weather)

        self.label1 = ttk.Label(self.root, font=title_font, foreground="white", background="turquoise")
        self.label1.pack()
        self.label2 = ttk.Label(self.root, font=info_font, foreground="white", background="turquoise")
        self.label2.pack()

    def get_weather(self, event):
        city = self.textField.get()
        try:
            corrected_city = self.correct_city_typo(city)

            if corrected_city in self.weather_cache:
                data = self.weather_cache[corrected_city]
                self.update_labels(data)
                self.priority_queue.push((self.cities_list.count(corrected_city), corrected_city))
            else:
                data = self.fetch_weather_data(corrected_city)
                self.weather_cache[corrected_city] = data
                self.update_labels(data)

                if corrected_city not in self.cities_list:
                    self.cities_list.append(corrected_city)
                    self.priority_queue.push((1, corrected_city))
                else:
                    index = self.cities_list.index(corrected_city)
                    freq, corrected_city = self.priority_queue.pop()
                    self.priority_queue.push((freq + 1, corrected_city))

            self.update_weather_graph(corrected_city)

            response = messagebox.askyesno("View Graph", "Do you want to view the weather trend graph?")
            if response:
                self.plot_weather_trend(corrected_city)

            response_activities = messagebox.askyesno("Outdoor Activities", "Do you want outdoor activity suggestions?")
            if response_activities:
                self.suggest_activities(data)

        except Exception as e:
            self.show_error("Error", "Could not fetch weather data")

    def fetch_weather_data(self, city):
        api_key = "91a68e80ddfd2874d7317c5ba27e5d9b"
        api = f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid=91a68e80ddfd2874d7317c5ba27e5d9b"
        response = requests.get(api)
        response.raise_for_status()
        return response.json()

    def update_labels(self, data):
        condition = data['weather'][0]['main']
        temp = int(data['main']['temp'] - 273.15)
        min_temp = int(data['main']['temp_min'] - 273.15)
        max_temp = int(data['main']['temp_max'] - 273.15)
        pressure = data['main']['pressure']
        humidity = data['main']['humidity']
        wind = data['wind']['speed']
        sunrise = time.strftime('%I:%M:%S', time.gmtime(data['sys']['sunrise'] - 21600))
        sunset = time.strftime('%I:%M:%S', time.gmtime(data['sys']['sunset'] - 21600))

        final_info = f"{condition}\n{temp}°C"
        final_data = f"\nMin Temp: {min_temp}°C\nMax Temp: {max_temp}°C\nPressure: {pressure}\nHumidity: {humidity}\nWind Speed: {wind}\nSunrise: {sunrise}\nSunset: {sunset}"

        self.label1.config(text=final_info)
        self.label2.config(text=final_data)

    def update_weather_graph(self, city):
        temperature_change = random.uniform(-5, 5)
        self.weather_graph.add_edge(city, temperature_change)

    def plot_weather_trend(self, city):
        plt.figure(figsize=(8, 5))
        days = range(1, len(self.weather_graph.get_neighbors(city)) + 1)
        temperatures = self.weather_graph.get_neighbors(city)

        plt.plot(days, temperatures, marker='o', linestyle='-', color='b', label='Temperature Change')
        plt.title(f"Weather Trend for {city}")
        plt.xlabel("Days")
        plt.ylabel("Temperature Change (°C)")
        plt.grid(True)
        for i, txt in enumerate(temperatures):
            plt.annotate(f'{txt:.2f}', (days[i], temperatures[i]), textcoords="offset points", xytext=(0, 10), ha='center')

        plt.legend()
        plt.show()

    def suggest_activities(self, data):
        suitable_activities = ""
        weather_condition = data['weather'][0]['main']
        temperature = int(data['main']['temp'] - 273.15)
        wind_speed = data['wind']['speed']

        suitable_activities += self.get_activities_based_on_temperature(temperature)
        suitable_activities += self.get_activities_based_on_weather_condition(weather_condition)
        suitable_activities += self.get_activities_based_on_wind_speed(wind_speed)

        self.show_activity_suggestion(suitable_activities)

    def get_activities_based_on_temperature(self, temperature):
        if temperature > 25:
            return "It's a Nice day for swimming or Maybe Hiking.\n"
        elif 15 <= temperature <= 25:
            return "Enjoy outdoor sports like Football or Cricket.\n"
        else:
            return "It's a bit chilly. You may want to consider indoor activities or wear layers for outdoor activities.\n"

    def get_activities_based_on_weather_condition(self, weather_condition):
        if weather_condition == 'Clear':
            return "Clear sky! Perfect for outdoor activities like running or cycling.\n"
        elif weather_condition == 'Clouds':
            return "Partly cloudy. You can enjoy activities like golf or tennis.\n"
        elif weather_condition == 'Rain':
            return "Rainy day. Consider indoor activities or play sports like table tennis or badminton.\n"
        elif weather_condition == 'Snow':
            return "Snowy weather! Try winter sports like skiing or snowboarding.\n"
        elif weather_condition == 'Thunderstorm':
            return "Thunderstorm! Stay indoors and avoid outdoor activities.\n"
        else:
            return "Check the weather and plan your outdoor activities accordingly.\n"

    def get_activities_based_on_wind_speed(self, wind_speed):
        if wind_speed > 20:
            return "It's windy! Consider activities that are less affected by wind, such as indoor sports.\n"
        else:
            return "The wind speed is moderate. You can enjoy a variety of outdoor activities.\n"

    def show_activity_suggestion(self, suggestion):
        messagebox.showinfo("Outdoor Activity Suggestion", suggestion)

    def show_error(self, title, message):
        messagebox.showerror(title, message)

root = tk.Tk()
app = WeatherApp(root)
root.mainloop()
