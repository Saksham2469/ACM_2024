import tkinter as tk
from tkinter import messagebox, scrolledtext, Canvas, Frame
import subprocess

def on_canvas_configure(event):
    canvas.configure(scrollregion=canvas.bbox("all"))

def create_task_input_fields():
    try:
        num_tasks = int(entry_num_tasks.get())

        if num_tasks <= 0:
            messagebox.showerror("Error", "Please enter a valid number of tasks (greater than zero).")
            return

        for widget in scrollable_frame.winfo_children():
            widget.destroy()

        tk.Label(scrollable_frame, text="Task Details", font=("Helvetica", 12, "bold")).grid(row=0, column=0, columnspan=4, pady=10)

        tk.Label(scrollable_frame, text="Burst Time", font=("Helvetica", 10)).grid(row=1, column=1, padx=10, pady=5)
        tk.Label(scrollable_frame, text="Arrival Time", font=("Helvetica", 10)).grid(row=1, column=2, padx=10, pady=5)
        tk.Label(scrollable_frame, text="Priority", font=("Helvetica", 10)).grid(row=1, column=3, padx=10, pady=5)

        global entry_burst_times, entry_arrival_times, entry_priorities
        entry_burst_times = []
        entry_arrival_times = []
        entry_priorities = []

        for i in range(num_tasks):
            tk.Label(scrollable_frame, text=f"Task {i + 1}", font=("Helvetica", 10)).grid(row=i + 2, column=0, padx=10, pady=5)
            entry_burst = tk.Entry(scrollable_frame, width=10, font=("Helvetica", 10))
            entry_burst.grid(row=i + 2, column=1, padx=10, pady=5)
            entry_arrival = tk.Entry(scrollable_frame, width=10, font=("Helvetica", 10))
            entry_arrival.grid(row=i + 2, column=2, padx=10, pady=5)
            entry_priority = tk.Entry(scrollable_frame, width=10, font=("Helvetica", 10))
            entry_priority.grid(row=i + 2, column=3, padx=10, pady=5)
            entry_burst_times.append(entry_burst)
            entry_arrival_times.append(entry_arrival)
            entry_priorities.append(entry_priority)

        canvas.update_idletasks()
        canvas.configure(scrollregion=canvas.bbox("all"))

        run_button.pack(pady=10)

    except ValueError:
        messagebox.showerror("Error", "Invalid number of tasks")

def run_cpp_program():
    try:
        num_tasks = int(entry_num_tasks.get())

        if num_tasks <= 0:
            messagebox.showerror("Error", "Please enter a valid number of tasks (greater than zero).")
            return

        tasks = []

        for i in range(num_tasks):
            burst_time = entry_burst_times[i].get().strip()
            arrival_time = entry_arrival_times[i].get().strip()
            priority = entry_priorities[i].get().strip()

            if not (burst_time and arrival_time and priority):
                messagebox.showerror("Error", "Please fill in all fields.")
                return

            try:
                burst_time = float(burst_time)
                arrival_time = float(arrival_time)
                priority = float(priority)

                if burst_time <= 0 or arrival_time < 0 or priority < 0:
                    messagebox.showerror("Error", "Invalid input values. Burst Time should be > 0, Arrival Time should be >= 0, and Priority should be >= 0.")
                    return

                tasks.append(f"{burst_time} {arrival_time} {priority}")

            except ValueError:
                messagebox.showerror("Error", "Please enter valid numerical values for Burst Time, Arrival Time, and Priority.")
                return

        quantum = float(entry_quantum.get().strip())

        if quantum <= 0:
            messagebox.showerror("Error", "Please enter a valid Round Robin quantum (greater than zero).")
            return

        user_input = f"{num_tasks}\n" + "\n".join(tasks) + f"\n{quantum}\n"
        print(f"User input to C++ program:\n{user_input}")

        result = subprocess.run(['./acm.exe'], input=user_input, text=True, capture_output=True)

        if result.returncode == 0:
            print(f"Program output:\n{result.stdout}")

            output_lines = result.stdout.splitlines()
            display_output(output_lines)
        else:
            messagebox.showerror("Error", f"Error running program: {result.stderr}")
            print(f"Error running program:\n{result.stderr}")

    except ValueError:
        messagebox.showerror("Error", "Please enter a valid numerical value for Round Robin quantum.")
    except Exception as e:
        messagebox.showerror("Error", f"An error occurred: {str(e)}")

def display_output(output_lines):
    for widget in result_text_frame.winfo_children():
        widget.destroy()

    headers = output_lines[0].split('|')
    for idx, header in enumerate(headers):
        tk.Label(result_text_frame, text=header.strip(), font=("Helvetica", 10, "bold")).grid(row=0, column=idx, padx=10, pady=5)

    for i, line in enumerate(output_lines[1:], start=1):
        data = line.split('|')
        for j, value in enumerate(data):
            entry = tk.Entry(result_text_frame, width=15, font=("Helvetica", 10))
            entry.grid(row=i, column=j, padx=10, pady=2, sticky="nsew")
            entry.insert(tk.END, value.strip())

    summary_label = tk.Label(result_text_frame, text="Summary Table (Avg Turnaround Time and Avg Waiting Time)", font=("Helvetica", 12, "bold"))
    summary_label.grid(row=len(output_lines) + 1, column=0, columnspan=len(headers), pady=10)

root = tk.Tk()
root.title("CPU Scheduling Simulator")
root.geometry("1000x600")
root.configure(bg="lightblue")

frame_num_tasks = tk.Frame(root, bg="lightblue")
frame_num_tasks.pack(pady=10)

label_num_tasks = tk.Label(frame_num_tasks, text="Enter Number of Tasks:", bg="lightblue", font=("Helvetica", 12))
label_num_tasks.grid(row=0, column=0, padx=10, pady=10)

entry_num_tasks = tk.Entry(frame_num_tasks, font=("Helvetica", 12), width=10)
entry_num_tasks.grid(row=0, column=1, padx=10, pady=10)

proceed_button = tk.Button(frame_num_tasks, text="Proceed", command=create_task_input_fields, bg="white")
proceed_button.grid(row=0, column=2, padx=10, pady=10)

canvas = Canvas(root, bg="lightblue", width=400)
canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

scrollbar = tk.Scrollbar(root, orient=tk.VERTICAL, command=canvas.yview)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

canvas.configure(yscrollcommand=scrollbar.set)

scrollable_frame = Frame(canvas, bg="lightblue")
scrollable_frame.bind(
    "<Configure>",
    lambda e: canvas.configure(
        scrollregion=canvas.bbox("all")
    )
)

canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")

canvas.bind("<Up>", lambda event: canvas.yview_scroll(-1, "units"))
canvas.bind("<Down>", lambda event: canvas.yview_scroll(1, "units"))
canvas.bind("<Prior>", lambda event: canvas.yview_scroll(-1, "pages"))
canvas.bind("<Next>", lambda event: canvas.yview_scroll(1, "pages"))

label_quantum = tk.Label(root, text="Round Robin Quantum:", bg="lightblue", font=("Helvetica", 12))
label_quantum.pack(pady=10)

entry_quantum = tk.Entry(root, font=("Helvetica", 12), width=10)
entry_quantum.pack(pady=10)

run_button = tk.Button(root, text="Run Program", command=run_cpp_program, bg="white")
run_button.pack_forget()

result_text_frame = Frame(root, bg="lightblue")
result_text_frame.pack(pady=10)

root.mainloop()
