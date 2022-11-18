<template>
  <form @submit="onSubmit">
    <label for="name">Book name:</label>
    <input type="text" id="name" name="book" v-model="addBookForm.name" required placeholder="Name"><br>
    <label for="author">Author:</label>
    <input type="text" id="author" name="author" v-model="addBookForm.author" required placeholder="Author"><br>
    <label for="publisher">Publisher:</label>
    <input type="text" id="publisher" name="publisher" v-model="addBookForm.publisher" required
      placeholder="Publisher"><br>
    <label for="pages">Page count:</label>
    <input type="text" id="pages" name="pages" v-model="addBookForm.pages" required placeholder="Pages"><br>
    <input @submit="onSubmit" type="submit" value="Submit">
  </form>


  <table>
    <thead>
      <tr>
        <th>Book</th>
        <th>Details</th>
      </tr>
    </thead>
    <tbody>
      <tr v-for="book in books" :key="book._id">
        <td>{{ book.name }}</td>
        <td>
          Author: {{ book.author }}<br>
          Publisher: {{ book.publisher }}<br>
          Pages: {{ book.pages }}
        </td>
        <td>
          <button @click="deleteBook(book._id)">Delete</button>
        </td>
      </tr>
    </tbody>
  </table>
</template>


<script>
import axios from 'axios'
export default {
  name: 'BooksComponent',
  data() {
    {
      return {
        books: [],
        addBookForm:
        {
          name: "",
          author: "",
          publisher: "",
          pages: ""
        }
      }
    }
  },
  methods: {
    getBooks() {
      axios.get("/api/books")
        .then((res) => {
          this.books = res.data
        })
        .catch((err) => {
          console.error(err)
        })
    },
    addBook(payload) {

      console.log(payload)
      axios.post("/api/books", payload)
        .then(() => {
          this.getBooks()
        })
        .catch((err) => {
          console.error(err)
        })
    },

    deleteBook(id) {
      axios.delete(`/api/book/${id}`)
        .then(() => {
          this.getBooks()
        })
        .catch((err) => {
          console.error(err)
        })
    },

    initForm() {
      this.addBookForm.name = ""
      this.addBookForm.author = ""
      this.addBookForm.publisher = ""
      this.addBookForm.pages = ""
    },

    onSubmit(e) {
      e.preventDefault();
      const payload = {
        name: this.addBookForm.name,
        author: this.addBookForm.author,
        publisher: this.addBookForm.publisher,
        pages: this.addBookForm.pages
      };
      this.addBook(payload)
      this.initForm;
    }

  },
  created() {
    this.getBooks();
  }

}
</script>
