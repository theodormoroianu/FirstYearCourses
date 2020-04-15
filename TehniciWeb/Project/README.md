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

## Reqired packages

Required `npm` packages are:
* express

``` bash
npm install express
```