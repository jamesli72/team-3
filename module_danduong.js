var path = require('path');
// Combining Directory Names
var directories = ["users", "mike", "docs"];
var docsDirectory = directories.join(path.sep);
console.log(' Document directory : %s', docsDirectory);
// Combining Directory Names and File Names
var curPath = path.join('/Users/mike', 'notepad.exe');
console.log(' File path: %s', curPath)
// Identifies directories, file names, and extensions in path
var filename = "C:\\Users\\mike\\notepad.exe";
var dirname = path.dirname (filename);
var basename = path.basename (filename);
var extname = path.extname (filename);
console.log('directory: %s, file name: %s, extension: %s',
    dirname, basename, extname);