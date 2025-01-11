def process_student_data(student_data: list[dict]):
    d = {}
    for student in student_data:
        l = student['grades']
        avg = 0
        for i in l:
            avg += i
        avg /= len(l)
        d[student['id']] = avg
    return d

student_data = [
    {'id': '1', 'grades': [85, 92, 78]},
    {'id': '2', 'grades': [95, 88, 92]},
    {'id': '3', 'grades': [70, 85, 90]}]

d = process_student_data(student_data)
print(d)