packge helper

import (
    "context"
    "encoding/json"
    "fmt"
    "log"
    "net/http"

    "go.mongodb.org/mongo-driver/mongo"
    "go.mongodb.org/mongo-driver/mongo/options"
)

// ConnectDB: This is a helper function to connect to mongoDB
// Upper-case start to expose the function to external classes
func ConnectDB() *mongo.Collection {
    // Set client options
    clientOptions := options.Client().ApplyURI("Cluster endpoint")

    // Connect to MongoDB
    client, err := mongo.Connect(context.TODO(), clientOptions)

    if err != nil {
        log.Fatal(err)
    }
    fmt.Println("Connected to MongoDB")
    collection := client.Database("go_rest_api").Collection("books")

    return collection
}

// ErrorResponse: Error model
type ErrorResponse struct {
    StatusCode int `json:"status"`
    ErrorMessage string `json:"message"`
}

// GetError: This is the helper function to prepare error model.
// Upper-case start to expose the function to external classes
func GetError(err error, w http.ResponseWriter) {
    log.Fatal(err.Error())

    var response = ErrorResponse {
        ErrorMessage: err.Error(),
        StatusCode: http.StatusInternalServerError,
    }

    message, _ := json.Marshal(response)

    w.WriteHeader(response.StatusCode)
    w.Write(message)
}

