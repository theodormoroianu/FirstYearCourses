Adam = {
    "Nume": "Adam",
    "Varsta": 12345,
    "calitati": ["batran", "primul om"]
}

function AddElement(object)
{
    body = document.getElementById('main');
    
    h = document.createElement('h2')
    h.appendChild(document.createTextNode('Lista cu proprietatile obiectului dat:'))

    ul = document.createElement('ul')
    
    Object.keys(object).forEach(element => {
        li = document.createElement('li')
        li.appendChild(document.createTextNode(
            element + ": " + object[element]
        ))
        ul.appendChild(li)
    })

    ul.appendChild(document.createTextNode("<li>Hello</li>"))

    body.appendChild(ul)    
}


AddElement(Adam)