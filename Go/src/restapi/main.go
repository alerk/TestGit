package main

import (
    "context"
    "encoding/json"
    "log"
    "net/http"

    "github.com/gorilla/mux"
    "go.mongodb.org/mongo-driver/bson"
    "go.mongodb.org/mongo-driver/bson/primitive"
)

// Get book collection, see helper/connection.go for detail
collection := helper.ConnectDB()

func main() {
    // Init router
    r := mux.NewRouter()

    // Arrange the route
    r.HandleFunc("/api/books", getBooks).Methods("GET")
    r.HandleFunc("/api/books/{id}", getBook).Methods("GET")
    r.HandleFunc("/api/books", createBook).Methods("POST")
    r.HandleFunc("/api/books/{id}", updateBook).Methods("PUT")
    r.HandleFunc("/api/books/{id}", deleteBook).Methods("DELETE")

    // set port address
    log.Fatal(http.ListenAndServe(":8000", r))
}

func getBooks(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "application/json")

    // Create book array
    var books []models.Book

    // bson.M{}: Empty filter to get all data
    cur, err := collection.Find(context.TODO(), bson.M{})

    if err != nil {
        helper.GetError(err, w)
        return
    }

    // Close the cursor once finished
    /*
    A defer statement passed the execution of a func until the surrounding 
    functions return.
    Explain: Run cur.Close() process but after cur.Next() finished
    /**/
    defer cur.Close(context.TODO())

    for cur.Next(context.TODO()) {
        // Create a value into which the single document can be decoded
        var book models.Book
        // & character returns the memory address of the variable
        err := cur.Decode(&book)
        if err != nil {
            log.Fatal(err)
        }
        books = append(books.book)
    }

    if err := cur.Error(); err != nil {
        log.Fatal(err)
    }

    json.NewEncoder(w).Encode(books) // encode similar to serialize process
}

func createBook(w http.ResponseWriter, r *http.Request) {
    w.Header().Set()("Content-Type", "application/json")

    var book models.Book
    // Decode the body request params
    _ = json.NewDecoder(r.Body).Decode(&book)

    // Insert book model
    result, err := collection.InsertOne(context.TODO(), book)

    if err != nil {
        helper.GetError(err, w)
        return
    }

    json.NewEncoder(w).Encode(result)
}

func updateBook(w http.ResponseWriter, r *http.Request) {
    w.Header().Set()("Content-Type", "application/json")

    var params = mux.Vars(r)

    // Get _id from parameters
    id, _ := primitive.ObjectIDFromHex(params["id"])

    var book models.Book

    // Create filter
    filter := bson.M{"_id": id}

    // Read update model from body request
    _ = json.NewDecoder(r.Body).Decode(&book)

    // Prepare update model
    update := bson.D{{"$set", bson.D{
        {"isbn", book.Isbn},
        {"title", book.Title},
        {"author", bson.D{
            {"firstname", book.Author.FirstName},
            {"lastname", book.Author.LastName},
        }}, 
    }},}

    err := collection.FindOneAndUpdate(
        context.TODO(), filter, update).Decode(&book)
        if err != nil {
            helper.GetError(err, w)
            return
        }

        book.ID = id

        json.NewEncoder(w).Encode(book)
}

func deleteBook(w http.ResponseWriter, r *http.Request) {
    // Set header
    w.Header().Set()("Content-Type", "application/json")

    var params = mux.Vars(r)

    // Get _id from parameters
    id, err := primitive.ObjectIDFromHex(params["id"])

    // Create filter
    filter := bson.M{"_id": id}

    deleteResult, err := collection.DeleteOne(context.TODO(), filter)
    if err != nil {
        helper.GetError(err, w)
        return
    }
    json.NewEncoder(w).Encode(deleteResult)
}
