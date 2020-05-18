# Documentation for the server

The core of the app will be on the client side, the only role of the server being:
* Serve the first `html` file (with a basic structure)
* Give to the client the required scripts / `css` files
* Verify the authenticity of the user who logged in (and of course create new users)
* Create new sessions by giving users authentification tokens
* Serve / Save / Delete notes via Create / Update / Delete requests

For making requests easier, I decided to use the `express` framework.

The server is able to:
    1. Receive `POST(/API/login)` from [here](login_signup.md) which:
        a. If the token / user is invalid it breaks
        b. If the user doesn't have a token yet it creates one
        c. returns a json with the user info

    2. Receive `POST(/API/signup)` from [here](login_signup.md) which:
        a. Verifies the info is corect is user doesn't exist
        b. Creates the new user, creates a token and returns the user json

    3. Receive `DELETE(/API/signout)` from [here](login_signup.md) which:
        Deletes the user token

    4. Receive `POST(/API/notes)` from [here](menu.md) which:
        Creates a new note

    5. Receive `DELETE(/API/notes)` from [here](menu.md) which:
        Deletes a note

    6. Receive `PUT(/API/notes)` from [here](menu.md) which:
        Updates a note

    7. Receive `GET(/API/notes)` from [here](menu.md) which:
        Returns a note

    8. Receive `PUT(/API/settings)` from [here](menu.md) which:
        updates settings for a user

    9. Receive `GET(/API/note_graph) from [here](menu.md) which:
        returns a picture with the note graph
    
    

    


