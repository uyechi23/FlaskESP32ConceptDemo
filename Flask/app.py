from flask import Flask

app = Flask(__name__)

# Human Route
@app.route('/potentiometer/human/<float:val>')
def humanpot(val):
    # check if data is valid (i.e., between 0-100)
    # if not valid, return a -1
    if not ((val >= 0.0) and (val <= 100.0)):
        return "<h1>Invalid number; please enter a value between 0.0 and 100.0.<h1>"
    
    # add data to a text file called "human.txt"
    with open("human.txt", "a") as file:
        file.write(f'{val}\n')
        
    # process the data in the file (e.g., an average)
    total = 0
    count = 0
    with open("human.txt", "r") as file:
        for line in file:
            total += float(line.rstrip())
            count += 1
        
    avg = total/count
    
    # for a HUMAN, we should return some text (HTML is optional)
    # that can be displayed on a web browser
    return f'<h1>The average of all human inputs is: {avg:.3f}<h1>'

# ESP32 Route
@app.route('/potentiometer/esp32/<float:val>')
def esp32pot(val):
    # check if data is valid (i.e., between 0-100)
    # if not valid, return a -1
    if not ((val >= 0.0) and (val <= 100.0)):
        return "-1"
    
    # add data to a text file called "esp32.txt"
    with open("esp32.txt", "a") as file:
        file.write(f'{val}\n')
        
    # process the data in the file (e.g., an average)
    total = 0
    count = 0
    with open("esp32.txt", "r") as file:
        for line in file:
            total += float(line.rstrip())
            count += 1
        
    avg = total/count
    
    # for an ESP32, we should return just the relevant data
    # for example, returning just the average would suffice
    # we can extrapolate the data in the ESP32 code
    return f'{avg}'