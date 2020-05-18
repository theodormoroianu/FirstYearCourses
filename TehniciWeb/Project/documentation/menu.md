# Documentation for the `MENU` file - AKA the notes manager

Javascript file taking care of managing the notes.

## For creating a new note, a JSON is sent to:
``` javascript
POST request to "API/notes"
var obj {
    token: 123,
    data: {
        note_id: Undefined,
        head: 0,
        versions: [{
            title: "note title",
            task: "note task",
            creation_date: "note_creation_date",
            deadline: "note_deadline",
            content: "note_content",
            asociated_picture: "link to the asociated_picture",
            origin: -1
        }]
    }
}
```

The server will respond with:
``` javascript
var obj {
    authentification: {
        authentificated: True / False,
        message: "OK" / error message
    },
    note_id: 123
}
```


## For deleting a note, a JSON is sent to:
``` javascript
DELETE request to "API/notes"
var obj {
    token: 123
    note_id: 123
}
``` 

The server will respond with:
``` javascript
var obj {
    authentification: {
        authentificated: True / False,
        message: "OK" / error message
    }
}
```


## When the client wants to get a note, he will perform a get request:
``` javascript
    GET request to "API/notes?token=123&note_id=234"
```

The server will answer with:
``` javascript
    var obj {
        authentification: {
            authentificated: True / False,
            message: "OK" / error message
        },
        data: {
            note_id: 123,
            head: 23,
            versions: [{
                title: "note title",
                task: "note task",
                creation_date: "note_creation_date",
                deadline: "note_deadline",
                content: "note_content",
                asociated_picture: "link to the asociated_picture",
                origin: 14
            }]
        }
    }
```


## For updating a note, a JSON is sent to:
``` javascript
    PUT request to "API/notes"
    var obj {
        token: 123
        data: {
            note_id: Undefined,
            head: 0,
            versions: [{
                title: "note title",
                task: "note task",
                creation_date: "note_creation_date",
                deadline: "note_deadline",
                content: "note_content",
                asociated_picture: "link to the asociated_picture",
                origin: -1
            }]
        }
    }
```

The server will answer with:
``` javascript
    var obj {
        authentification: {
            authentificated: True / False,
            message: "OK" / error message
        }
    }
```


## For modifying the settings, a JSON is sent to:
``` javascript
PUT request to "API/settings"
var obj {
    token: 123
    info: {
        name: /// new name
        password: /// new password
    },
    config: {
        sort_notes_by: "deadline / creation / alphabetical",
        sort_asc: True / False,
        stay_signed_in: True / False,
        avatar_url: "link to the avatar picture"
    }
}
```

The server will answer with:
``` javascript
var obj {
    authentification: {
        authentificated: True / False,
        message: "OK" / error message
    }
}
```


## When the client wants to get the picture graph of a note, he will perform a get request:
``` javascript
    GET request to "API/note_graph?note_id=234"
```

The server will answer with the given picture

