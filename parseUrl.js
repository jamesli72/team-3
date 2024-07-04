var url = require('url');
var curURL = url.parse(
    'https://www.google.com/search?query=steve+jobs');
    var curStr = url.format(curURL);

console.log('address string : %s', curStr);
console.dir(curURL);

var querystring = require('querystring');
var param = querystring.parse(curURL.query);
console.log('query value in the query parameters : %s', param.query);
console.log('original query parameter : %s', querystring.stringify(param));