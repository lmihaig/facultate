from flask import Flask, render_template, request
import requests
import hashlib
from pathvalidate import sanitize_filename

app = Flask(__name__)


@app.route("/", methods=["GET", "POST"])
def Index():
    if request.method == "POST":
        url = request.form["url"]
        name = request.form["name"]
        print(url)
        try:
            image = requests.get(url).content
            name = sanitize_filename(name)
            if not name:
                name = hashlib.sha256(image).hexdigest()
            with open(f"images/{name}.png", "wb") as handler:
                handler.write(image)
        except Exception:
            print("No valid image at url")

    return render_template("index.html")


if __name__ == "__main__":
    app.run(debug=True)
