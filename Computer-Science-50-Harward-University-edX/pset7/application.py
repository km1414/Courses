from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():

    # get distinct stock symbols from hitory
    stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = :user_id", user_id=session["user_id"])

    # useful variable
    portfolio_data = []
    balance = None
    total_value = None
    counter = 0

    # analyzing every stock from portfolio
    for stock in stocks:
        symbol = stock['symbol']

        # get number of shares
        buy_total = db.execute("SELECT TOTAL (count) FROM history WHERE user_id=:user_id AND symbol=:symbol AND operation=:op",
                                user_id=session["user_id"], symbol=symbol, op="buy")[0]["TOTAL (count)"]

        sell_total = db.execute("SELECT TOTAL (count) FROM history WHERE user_id=:user_id AND symbol=:symbol AND operation=:op",
                                user_id=session["user_id"], symbol=symbol, op="sell")[0]["TOTAL (count)"]

        shares_num = buy_total - sell_total

        # get current price
        price = lookup(symbol)

        # ensure conection was successful
        if price is None:
            return apology("connection lost. try again")

        # get current balance (only first time)
        if balance is None:
            balance = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
            total_value = balance

        # add value of stock to total portfolio value
        total_value += price["price"] * shares_num

        if total_value is None:
            total_value = balance

        # put data to dictionary
        portfolio_data.append({})
        portfolio_data[counter]["symbol"] = symbol
        portfolio_data[counter]["shares"] = shares_num
        portfolio_data[counter]["price"] = usd(price["price"])
        portfolio_data[counter]["value"] = usd(price["price"] * shares_num)
        counter += 1

    # if no stocks in portfolio
    if balance is None:
        balance = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        total_value = balance

    return render_template("index.html", portfolio_data=portfolio_data, balance=usd(balance), total_value=usd(total_value))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # ensure number of shares was submitted
        if not request.form.get("symbol"):
            return apology("must provide number of shares")

        # ensure number of shares was submitted
        if int(request.form.get("number")) <= 0:
            return apology("must provide exact positive number of shares")

        # get current price of stock
        output = lookup(request.form.get("symbol").upper())

        # ensure symbol is correct
        if output is None:
            return apology("symbol incorrect")

        # useful variables
        price = output["price"]
        count = int(request.form.get("number"))


        # get user current balance
        balance = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]

        # ensure sufficient balance
        if balance < price * count:
            return apology("not enough money")

        # create table for history (if not exist yet)
        db.execute("CREATE TABLE IF NOT EXISTS 'history' ('user_id' INTEGER NOT NULL, 'symbol' TEXT NOT NULL,\
                       'count' INTEGER NOT NULL, 'price' NUMERIC NOT NULL,\
                       'operation' TEXT NOT NULL, 'date' DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP)")

        # insert entry to history
        db.execute("INSERT INTO history (user_id, symbol, count, price, operation)\
                    VALUES (:user_id, :symbol, :count, :price, :operation)",
                   user_id=session["user_id"],
                   symbol=request.form.get("symbol").upper(),
                   count=count,
                   price=price,
                   operation="buy")

        # update users balance
        db.execute("UPDATE users SET cash = cash - :transaction  WHERE id = :user_id",
                    user_id=session["user_id"], transaction = price * count)

        return render_template("buy.html")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    history = db.execute("SELECT * FROM history WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", history=history)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # get current price of stock
        output = lookup(request.form.get("symbol").upper())

        # ensure symbol is correct
        if output is None:
            return apology("symbol incorrect")


        return render_template("quoted.html", output=output)

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure username doesn't exist yet
        if len(db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))) > 0:
            return apology("username already exists")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure password was repeated
        elif not request.form.get("password_repeat"):
            return apology("must repeat password")

        # ensure password was repeated correctly
        elif request.form.get("password") != request.form.get("password_repeat"):
            return apology("must repeat password correctly")

        # insert new user into users
        db.execute("INSERT INTO users (username, hash) VALUES (:username_val, :hash_val)",
                   username_val=request.form.get("username"), hash_val=pwd_context.hash(request.form.get("password")))

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # ensure number of shares was submitted
        if not request.form.get("symbol"):
            return apology("must provide number of shares")

        # ensure number of shares was submitted
        if int(request.form.get("number")) <= 0:
            return apology("must provide exact positive number of shares")

        # get current price of stock
        output = lookup(request.form.get("symbol").upper())

        # ensure symbol is correct
        if output is None:
            return apology("symbol incorrect")

        # useful variables
        price = output["price"]
        count = int(request.form.get("number"))


        # get number of existing shares
        buy_total = db.execute("SELECT TOTAL (count) FROM history WHERE user_id=:user_id AND symbol=:symbol AND operation=:op",
                                    user_id=session["user_id"], symbol=request.form.get("symbol").upper(), op="buy")[0]["TOTAL (count)"]

        sell_total = db.execute("SELECT TOTAL (count) FROM history WHERE user_id=:user_id AND symbol=:symbol AND operation=:op",
                                    user_id=session["user_id"], symbol=request.form.get("symbol").upper(), op="sell")[0]["TOTAL (count)"]

        count_current = buy_total - sell_total

        # ensure sufficient stock's shares
        if count > count_current:
            return apology("you have only "+str(count_current)+" shares")


        # insert entry to history
        db.execute("INSERT INTO history (user_id, symbol, count, price, operation)\
                    VALUES (:user_id, :symbol, :count, :price, :operation)",
                    user_id=session["user_id"],
                    symbol=request.form.get("symbol").upper(),
                    count=count,
                    price=price,
                    operation="sell")

        # update users balance
        db.execute("UPDATE users SET cash = cash + :transaction  WHERE id = :user_id",
                    user_id=session["user_id"], transaction = price * count)

        return render_template("sell.html")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")


@app.route("/cash_in", methods=["GET", "POST"])
@login_required
def cash_in():
    """Add more cash to account."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure number of shares was submitted
        if int(request.form.get("number")) <= 0:
            return apology("must provide positive amount of money")

        # variable for sum
        money = int(request.form.get("number"))

        # update users balance
        db.execute("UPDATE users SET cash = cash + :transaction  WHERE id = :user_id",
                    user_id=session["user_id"], transaction = money)

        return render_template("cash_in.html")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("cash_in.html")