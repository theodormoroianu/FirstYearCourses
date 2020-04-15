var f = (obj) => {
    obj.data = 2;
};

var o = {
    data: 1
};

f(o);

console.log(o);