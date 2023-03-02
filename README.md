# FlaskESP32ConceptDemo
This is a demonstration repository for using Flask and ESP32 together. The "sensor" for this project is a potentiometer, and the ESP32 will read this value every 5 seconds and send it to the Flask app. The Flask app will then calculate the average of all stored values, and return the average to the ESP32. There is also a human route as a proof-of-concept that will demonstrate the difference between using Flask with a phone/computer and using Flask with an ESP32 for IoT purposes.

Note: The following are Windows-only instructions - I haven't had time or equipment to test this on Mac- or Linux-based computers. The process is the same, but the commands will vary based on your OS.

## Setup Instructions
First, clone the repository to your computer:
```
git clone https://github.com/uyechi23/FlaskESP32ConceptDemo
```

Once this is cloned, there will be two directories inside: Flask and ESP32.

### Flask Setup
For the Flask application, we want to first start up a virtual environment. Run the following command:
```
py -m venv env
```

This will create a virtual environment called "env". Virtual environments are rather large, so you normally won't add an entire virtual environment to GitHub. Instead, we can use a "requirements.txt" file to set up the virtual environment with the exact same dependencies as someone else's virtual environment. Use the following command to install the requirements from the text file:
```
py -m pip install -r requirements.txt
```

Then, activate the virtual environment (first line - Windows, second line - Mac/Linux):
```
env\Scripts\activate
source env/scripts/activate
```

You should now be able to run the Flask app using the following command:
```
flask run -h 0.0.0.0 -p 5000
```

### ESP32 Setup
The ESP32 folder contains the .ino file you can upload directly to the ESP32.
