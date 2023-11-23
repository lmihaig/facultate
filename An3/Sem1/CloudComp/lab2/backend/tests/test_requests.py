import json
from app import app

book1 = {
    "name": "1984",
    "author": "George Orwell",
    "publisher": "Penguin Books",
    "pages": 324,
}

book2 = {
    "name": "Animal Farm",
    "author": "George Orwell",
    "publisher": "Penguin Books",
    "pages": 234,
}

book3 = {
    "name": "I, Robot",
    "author": "Isaac Asimov",
    "publisher": "Harper Collins",
    "pages": 133,
}

book4 = {
    "name": "The Institute",
    "author": "Stephen King",
    "publisher": "Scribner",
    "pages": 439,
}

book5 = {
    "name": "Cryptonomicon",
    "author": "Neal Stephenson",
    "publisher": "Avon",
    "pages": 0,
}

books = [book1, book2, book3, book4, book5]

test_client = app.test_client()
id = 0
id_2 = 0


def test_delete_all_books():
    response = test_client.delete("/api/books")
    res = response.data.decode("utf-8")
    print("1", res)
    print(response.status_code)
    assert response.status_code == 204
    assert res == ""


def test_get_all_books():
    response = test_client.get("/api/books")
    res = json.loads(response.data.decode("utf-8"))
    print("2", res)
    assert response.status_code == 200
    assert type(res) is list
    assert res == []


def test_post_books():
    global id, id_2
    responses = [test_client.post("/api/books", json=book) for book in books]
    res = [json.loads(response.data.decode("utf-8")) for response in responses]
    id = res[0]["_id"]
    id_2 = res[3]["_id"]
    print("3", res)
    assert responses[0].status_code == 201
    assert type(res[0]) is dict
    assert "_id" in res[0].keys()


def test_get_all_books_2():
    response = test_client.get("/api/books")
    res = json.loads(response.data.decode("utf-8"))
    print("4", res)
    assert response.status_code == 200
    assert type(res) is list
    assert res


def test_get_one_book_1():
    response = test_client.get(f"/api/book/{id}")
    res = json.loads(response.data.decode("utf-8"))
    print("5", res)
    assert response.status_code == 200
    assert res["name"] == "1984"


def test_delete_one_book():
    response = test_client.delete(f"/api/book/{id}")
    res = response.data.decode("utf-8")
    print("6", res)
    assert response.status_code == 204
    assert res == ""


def test_get_one_book_2():
    response = test_client.get(f"/api/book/{id}")
    res = json.loads(response.data.decode("utf-8"))
    print("7", res)
    assert response.status_code == 404


def test_update_one_book_1():
    new_book_info = {"name": "TESTESTESTEST"}
    response = test_client.put(f"/api/book/{id}", json=new_book_info)
    res = response.data.decode("utf-8")
    print("8", res)
    assert response.status_code == 404


def test_update_one_book_2():
    new_book_info = {"name": "RACECARRACECAR"}
    response = test_client.put(f"/api/book/{id_2}", json=new_book_info)
    res = response.data.decode("utf-8")
    print("8", res)
    assert response.status_code == 201
