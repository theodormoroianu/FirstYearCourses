# Documentation for the login / signup

Javascript files taking care of the sign-up and sign-in operations.


## For signing in, the webapp sends:
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

## For creating a new account, a JSON is sent to:
``` javascript
POST request to "API/signup" /// creates a new user AND a new session
var obj {
    user: "name"
    name: "Name"
    password: "password"
}
```

## For signing out, a JSON is sent to:
``` javascript
DELETE request to "API/signout"
var obj {
    token: "123"
}
```

## In the first two cases, the server will ALWAYS answer with another json, containing:
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
