
from flask import Flask
from engine import Engine

app = Flask(__name__)

@app.route("/")
def main():
    testEngine = Engine()
    testEngine._execute_session()

    return "BackTest Complete"

if __name__ == "__main__":
    app.run()


