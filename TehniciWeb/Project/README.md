# TW project

_Project made in pure JS for the front end and express-js for the backend._

### General Idea

The idea of the project is to create a very lightweight web application able to store notes.
In it's final state, the app should be able to:
* Prompt the user to log-in or create a new account
* Have a list with all available notes, and offer the option to rename, remove or create new notes
* Open a note (which will most probably remain a `textbox` widget)
* Save any modification made online to the server

## Server

The core of the app will be on the client side, the only role of the server being:
* Serve the first `html` file (with a basic structure)
* Give to the client the required scripts / `css` files
* Verify the authenticity of the user who logged in (and of course create new users)
* Syncronize the notes (basically recive a `POST` request every few seconds and store it in a local file)

For making requests easier, I decided to use the `express` framework.

## Client

The Client app is made in pure `javascript`, and should consist of 3 different parts:

1. Log-in page
    * Page that opens by default unless the user is already signed-in
    * Requests for a user / password or offers to create a new account
    * Sends the info to the server and waits for a confirmation / denial
2. Interface
    * Script able to generate the main aspects of the app, like menus, notes, etc
    * Refreshes live based on the active user / notes
3. SyncService
    * Launches as soon as the user signs in
    * Fetches from the server a `JSON` containing all the data from the user
    * Once every few seconds it sends back the updated `JSON` to the server


## Behaviour

I will probably use the template now in `sample_website2`.
This will be the main page, from where we can access the list of all notes (the css-grid at the bottom), the "create a new Note", "settings" and "sign out" buttons.

The notes have:
* A category (work, travel, cook, bills, groceries etc).
* An asociated picture (most probably chosen randomly from a list on the server).
* A title
* A deadline
* A content (text)

The list on the main page will display:
* All the notes in the order of the deadline
* Each note will contain the title trimed to a certain lenght and the picture asociated with the note

The `new note` option will have the same efect than clicking on an existing note:
* It will replace the main page with a new one
* At the top of the page there will be a text box containing the title of the note
* Two buttons (save / discard)
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
The script checks if there is any user / password stored in the localstorage, and if not pops up the login page.

For signing in, the webapp sends:
```javascript
POST request to "API/login"
var obj {
    info: {
        user: "username",
        name: "User Name",
        password: "U$3RNAM3"
    }
}
```

For creating a new account, the JSON is sent to:
```javascript
POST request to "API/signup"
```

The server will ALWAYS answer with another json, containing:
```javascript
var obj {
    authentification: {
        authentificated: True / False,
        message: "OK" / error message
    }
    info: {
        user: /// username
        name: /// name
        password: /// password
    },
    config: {
        sort_notes_by: "deadline / creation / alphabetical",
        sort_asc: True / False,
        stay_signed_in: True / False,
        avatar_url: "link to the avatar picture"
    },
    data: [{
        title: "note title",
        task: "note task",
        creation_date: "note_creation_date",
        deadline: "note_deadline",
        content: "note_content",
        asociated_picture: "link to the asociated_picture"
    }]
}
```

Whenever the client feels like it, he can save the changes from the client by making:
```javascript
POST request to "API/checkpoint"
var obj {
    info: {
        user: /// username
        name: /// name
        password: /// password
        new_password: /// new password, empty if not changed
    },
    config: {
        sort_note_by: "Deadline / Creation Date / Alphabetical",
        sort_asc: True / False,
        stay_signed_in: True / False,
        avatar_url: "link to the avatar picture"

    },
    data: [{
        title: "note title",
        task: "note task",
        creation_date: "note_creation_date",
        deadline: "note_deadline",
        content: "note_content",
        asociated_picture: "link to the asociated_picture"
    }]
}
```

The server will respond with 

## Classes:
* Work
* Family
* Cooking
* Traveling
* Having Fun

## LocalStorage
* The localstorage stores the creditentials if the setting is enabled.
* It will store strigify({ user: "username", password: "Password" })

## Reqired packages

Required `npm` packages are:
* express

``` bash
npm install express
```


## ISSUES

1. For some reason, the name is lost from the sign-up to the menu
1. Unable to press 'discard' if all elements are not non-empty in forms