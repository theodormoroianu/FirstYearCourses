# TW project

_Project made in pure JS for the front end and express-js for the backend._

### General Idea

The idea of the project is to create a very lightweight web application able to store notes.
The app is able to:
* Prompt the user to log-in or create a new account
* Have a list with all available notes, and offer the option to rename, remove or create new notes
* Open a note
* Save any modification made online to the server
* Save creditentials in localstorage

## Server

The core of the app will be on the client side, the only role of the server being:
* Serve the first `html` file (with a basic structure)
* Give to the client the required scripts / `css` files
* Verify the authenticity of the user who logged in (and of course create new users)
* Create new sessions by giving users authentification tokens
* Serve / Save / Delete notes via Create / Update / Delete requests

For making requests easier, I decided to use the `express` framework.

## Client

The Client app is made in pure `javascript`, and consists of 3 different parts:

1. Log-in page
    * Page that opens by default unless the user is already signed-in
    * Requests for a user / password or offers to create a new account
    * Sends the info to the server and waits for a confirmation / denial
2. Sign-up page
    * Page where the user is able to create a new account
    * Sends the info to the server and waits for a confirmation
3. Interface
    * Script able to generate the main aspects of the app, like menus, notes, etc
    * Refreshes live based on the active user / notes
4. Settings
    * Offers the user a few settings like whether to keep it signed in or not, order of 
    the notes, avatar image etc
5. Note editor
    * Interface in which a user is able to create / edit / delete notes

## Behaviour

The notes have:
* A category (work, travel, cook, bills, groceries etc)
* An asociated picture (chosen randomly from a list on the server)
* A title
* A deadline
* A content (text)

The list on the main page will display:
* All the notes in the order of the deadline
* Each note will contain the title trimed to a certain lenght and the picture asociated with the note

The `new note` option will have the same efect than clicking on an existing note:
* It will replace the main page with a new one
* At the top of the page there will be a text box containing the title of the note
* Three buttons (save / discard / delete)
* A date chooser
* A text box containing the actual content of the note

The `sign out` button will force-clear the local storage, and send the user back to the login page.

The `settings` button will provide a few options like:
* Save creditentials (stay signed-in)
* Send an alert when aproaching a deadline
* Sort the Notes alphabetically, by the creation date or by the deadline, ascending or descending
* Change avatar with a picture from the internet (with a link)
* Change the password

## Details

When the first page is requested, the server sends an empty html with the main script.
The script checks if there is any token stored in the localstorage, and if not pops up the login page.

## User manager

    For signing in, the webapp sends:
``` javascript
    POST request to "API/login" /// creates a new session
    var obj {
        use_token: true/false
        /// if use_token = true
        token: "123"
        /// else
        user: "name"
        password: "password"
    }
```

    For creating a new account, a JSON is sent to:
``` javascript
    POST request to "API/signup" /// creates a new user AND a new session
    var obj {
        user: "name"
        name: "Name"
        password: "password"
    }
```

    For signing out, a JSON is sent to:
``` javascript
    DELETE request to "API/signout"
    var obj {
        token: "123"
    }
```

    In the first two cases, the server will ALWAYS answer with another json, containing:
``` javascript
    var obj {
        authentification: {
            authentificated: True / False,
            message: "OK" / error message
        }
        info: {
            user: /// username
            name: /// name
            token: /// authentification token
        },
        config: {
            sort_notes_by: "deadline / creation / alphabetical",
            sort_asc: True / False,
            stay_signed_in: True / False,
            avatar_url: "link to the avatar picture"
        },
        notes: [1, 2, 3, ...] /// list of notes
    }
```

## Notes manager
    
    1. For creating a new empty note, a JSON is sent to:
``` javascript
    POST request to "API/notes"
    var obj {
        token: 123,
        data: {
            node_id: 123,
            title: "note title",
            task: "note task",
            creation_date: "note_creation_date",
            deadline: "note_deadline",
            content: "note_content",
            asociated_picture: "link to the asociated_picture"
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


    
    2. For deleting a note, a JSON is sent to:
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



    3. When the client wants to get a note, he will perform a get request:
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
            node_id: 123,
            title: "note title",
            task: "note task",
            creation_date: "note_creation_date",
            deadline: "note_deadline",
            content: "note_content",
            asociated_picture: "link to the asociated_picture"
        }
    }
```


   
    4. For modifying a note, a JSON is sent to:
``` javascript
    PUT request to "API/notes"
    var obj {
        token: 123
        data: {
            note_id: 123
            title: "note title",
            task: "note task",
            creation_date: "note_creation_date",
            deadline: "note_deadline",
            content: "note_content",
            asociated_picture: "link to the asociated_picture"
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

## Settings manager
     4. For modifying the settings, a JSON is sent to:
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
        },
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

## Classes:
* Work
* Family
* Cooking
* Traveling
* Having Fun

## LocalStorage
* The localstorage stores the creditentials if the setting is enabled.
* It will store the token

## Reqired packages

Required `npm` packages are:
* express

``` bash
npm install express
```
