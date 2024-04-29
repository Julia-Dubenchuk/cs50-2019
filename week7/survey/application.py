import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("name")
    house = request.form.get("house")
    position = request.form.get("position")
    consent = request.form.get("consent")

    if not name:
        return render_template("error.html", message="Missing name.")
    elif not house:
        return render_template("error.html", message="Missing house.")
    elif not consent:
        return render_template("error.html", message="Missing consent.")

    with open('survey.csv', 'a') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=['name', 'house', 'position', 'consent'])
        writer.writerow({'name': name, 'house': house, 'position': position, 'consent': consent})

    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open('survey.csv', 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        data=list(reader)
        
    return render_template("sheet.html", data=data)
