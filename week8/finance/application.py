import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

os.environ["API_KEY"] = "pk_0a6ef0c1226b4521b2c58c4089f91d99"

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    data = {}
    cash_row = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    data["cash"] = usd(cash_row[0]["cash"])
    data["total"] = cash_row[0]["cash"]
    data["rows"] = []
    purchased_share_rows = db.execute("SELECT quote_id, symbol, SUM(shares) sum_shares, price FROM shares INNER JOIN quotes ON quotes.id = shares.quote_id WHERE shares.user_id = :user_id GROUP BY quote_id HAVING sum_shares > 0", user_id=session["user_id"])
    for row in purchased_share_rows:
        quote = lookup(row["symbol"])

        if quote == None:
            return apology(f"Invalid symbol {row["symbol"]}", 400)

        if row["price"] != quote["price"]:
            db.execute("UPDATE quotes SET price = :price WHERE id = :id", price=quote["price"], id=row["quote_id"])

        total = quote["price"] * row["sum_shares"]
        data["rows"].append({
            "symbol": row["symbol"],
            "shares": row["sum_shares"],
            "price": usd(quote["price"]),
            "total": usd(total)
        })
        data["total"] += total

    data["total"] = usd(data["total"])

    return render_template("index.html", data=data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if request.method == "POST":
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)

        quote = lookup(symbol)
        if quote == None:
            return apology("Invalid symbol", 400)

        cash_row = db.execute("SELECT cash FROM users WHERE id = :id ", id=session["user_id"])

        total_price = quote["price"] * int(shares)

        if total_price > cash_row[0]["cash"]:
            return apology("Can't afford", 400)

        quotes_row = db.execute("SELECT * FROM quotes WHERE symbol = :symbol", symbol=quote["symbol"])

        if len(quotes_row) == 1 and quotes_row[0]["price"] != quote["price"]:
            db.execute("UPDATE quotes SET price = :price WHERE id = :id", price=quote["price"], id=quotes_row[0]["id"])
        elif len(quotes_row) == 0:
            db.execute("INSERT INTO quotes (name, price, symbol) VALUES (:name, :price, :symbol)", name=quote["name"], price=quote["price"], symbol=quote["symbol"])

        quotes_row = db.execute("SELECT * FROM quotes WHERE symbol = :symbol", symbol=quote["symbol"])
        db.execute("INSERT INTO shares (user_id, quote_id, shares) VALUES (:user_id, :quote_id, :shares)", user_id=session["user_id"], quote_id=quotes_row[0]["id"], shares=shares)
        updated_cash = cash_row[0]["cash"] - total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=updated_cash, id=session["user_id"])

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get("username")

    if not username:
        return jsonify(False)

    rows = db.execute("SELECT username FROM users")

    for row in rows:
        if row["username"] == username:
            return jsonify(False)

    return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    share_rows = db.execute("SELECT symbol, shares, price, date FROM shares INNER JOIN quotes ON quotes.id = shares.quote_id WHERE user_id = :user_id", user_id=session["user_id"])

    for row in share_rows:
        row["price"] = usd(row["price"])

    return render_template("history.html", rows=share_rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        data = lookup(request.form.get("symbol"))
        data["price"] = usd(data["price"])

        return render_template("quoted.html", data=data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 403)
        elif not password:
            return apology("must provide password", 403)
        elif not confirm_password:
            return apology("must provide confirmation password", 403)
        elif password != confirm_password:
            return apology("Passwords don't match", 403)

        rows = db.execute("SELECT username FROM users")

        for row in rows:
            if row["username"] == username:
                return apology("Username is not available", 403)

        hash = generate_password_hash(password)
        key = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hash)

        if not key:
            return apology("Something happens. Please, try later.", 500)

        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    quote_id = request.form.get("symbol")
    shares = request.form.get("shares")
    purchased_share_rows = db.execute("SELECT quote_id id, symbol FROM shares INNER JOIN quotes ON quotes.id = shares.quote_id WHERE shares.user_id = :user_id GROUP BY quote_id", user_id=session["user_id"])
    symbols = []

    if len(purchased_share_rows) == 0:
        return apology("you don't have any shares", 400)

    for row in purchased_share_rows:
        symbols.append({
            "id": row["id"],
            "symbol": row["symbol"]
        })

    if request.method == "POST":
        if not quote_id:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)

        db_shares_row = db.execute("SELECT SUM(shares) sum_shares, price FROM shares INNER JOIN quotes ON quotes.id = shares.quote_id WHERE quote_id = :quote_id  GROUP BY quote_id", quote_id=quote_id)

        if int(shares) > db_shares_row[0]["sum_shares"]:
            return apology("too many shares", 400)

        # 1. add sell in table shares
        db.execute("INSERT INTO shares (user_id, quote_id, shares) VALUES (:user_id, :quote_id, :shares)", user_id=session["user_id"], quote_id=quote_id, shares=-int(shares))
        # 2. recalculate cash to add sum from sell to my cash
        cash_row = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash_row[0]["cash"] + db_shares_row[0]["price"] * int(shares), id=session["user_id"])
        return redirect("/")
    else:
        return render_template("sell.html", symbols=symbols)


@app.route("/settings", methods=["GET", "POST"])
def settings():
    """Change password"""
    if request.method == "POST":
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirmation")

        if not old_password:
            return apology("must provide old password", 403)
        elif not new_password:
            return apology("must provide new password", 403)
        elif not confirm_password:
            return apology("must provide confirmation password", 403)
        elif new_password != confirm_password:
            return apology("Passwords don't match", 403)

        rows = db.execute("SELECT hash FROM users WHERE id = :id", id=session["user_id"])

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], old_password):
            return apology("invalid old password", 403)

        hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = :hash WHERE id = :id", hash=hash, id=session["user_id"])

        return render_template("settings.html", success_updated=True)
    else:
        return render_template("settings.html", success_updated=False)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
