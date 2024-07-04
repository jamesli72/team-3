var url = require('url');
var curURL = url.parse(
    'https://www.google.com/search?query=steve+jobs');
    var curStr = url.format(curURL);

console.log('address string : %s', curStr);
console.dir(curURL);