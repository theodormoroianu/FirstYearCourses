var f = (obj) => {
    obj.data = 2;
};

var o = {
    data: 1
};

f(o);

console.log(o);


var obj = {
    nume: "Tata",
    copii: 3,
    nume_copii: {
        copil1: "Teo",
        copil2: "Lulu"
    },
    case: [
        {
            nume: "Cutu",
            locatie: "Sector4"
        },
        {
            nume: "Roma",
            locatie: "roma"
        }
    ]
};

console.log(obj);

console.log(JSON.stringify(obj));