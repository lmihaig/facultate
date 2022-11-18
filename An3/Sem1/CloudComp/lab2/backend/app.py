# TODO: ditch flask_restful move to flask_restx or smth else
from bson.objectid import ObjectId
from flask_pymongo import PyMongo
import pymongo
from flask import Flask, jsonify
from flask_restful import Api, Resource, abort, reqparse
import os
app = Flask(__name__)
app.config["SECRET_KEY"] = "csrf_token"

api = Api(app)

app.config["MONGO_URI"] = 'mongodb://' + os.environ['MONGODB_HOSTNAME'] + ':27017/' + os.environ['MONGODB_DATABASE']
# app.config["MONGO_URI"] = 'mongodb://localhost:27017/library'
mongo = PyMongo(app)
db = mongo.db


def positive(value):
    value = int(value)
    if not isinstance(value, int):
        raise ValueError(f"The value {value} is not an integer")

    if not value > 0:
        raise ValueError(f"The value {value} is not positive")

    return value


parser = reqparse.RequestParser()
parser.add_argument("name")
parser.add_argument("author")
parser.add_argument("publisher")
parser.add_argument("pages", type=positive)


def abort_if_book_doesnt_exist(book_id):
    response = list(db.books.find({"_id": ObjectId(book_id)}))
    if [] == response:
        abort(404, message=f"Book {book_id} doesn't exist")
    return response[0]


def abort_if_book_exists(book):
    response = db.books.find(book)
    if [] != list(response):
        abort(404, message=f"Book {book} already exists")
    return response


def export(books):
    for book in books:
        book["_id"] = str(book["_id"])
    return books


class booksApi(Resource):
    def get(self):
        return jsonify(export(list(db.books.find())))

    def post(self):
        args = parser.parse_args()
        book = {"name": args["name"], "author": args["author"],
                "publisher": args["publisher"], "pages": args["pages"]}
        abort_if_book_exists(book)
        id = db.books.insert_one(book)
        return {"_id": str(id.inserted_id)}, 201

    def delete(self):
        db.books.delete_many({})
        return "", 204


class bookApi(Resource):
    def get(self, id):
        response = abort_if_book_doesnt_exist(id)
        return export([response])[0]

    def put(self, id):
        args = dict(parser.parse_args())
        args = {key: val for key, val in args.items() if val}
        response = db.books.find_one_and_update(
            {"_id": ObjectId(id)}, {"$set": args},
            return_document=pymongo.ReturnDocument.AFTER)
        if not response:
            abort(404, message=f"Book {id} not found")
        return export([response])[0], 201

    def delete(self, id):
        abort_if_book_doesnt_exist(id)
        db.books.delete_one({"_id": ObjectId(id)})
        return "", 204


api.add_resource(booksApi, "/api/books")
api.add_resource(bookApi, "/api/book/<string:id>")

if __name__ == "__main__":
    ENVIRONMENT_DEBUG = os.environ.get("APP_DEBUG", True)
    ENVIRONMENT_PORT = os.environ.get("APP_PORT", 5000)
    app.run(port=ENVIRONMENT_PORT, debug=ENVIRONMENT_DEBUG)
