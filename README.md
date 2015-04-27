# pr.6-Server

Project 6: You Got Served

Due by: Friday, May 1, 2015 at 11:59pm

Introduction

Many years ago, someone invented the Internet, although some controversy still remains over who did it. A while after the Internet was invented, people came up with the idea of displaying information on webpages. These crude documents evolved over time to become the rather frightening explosion of information that we love, hate, rely on, use to waste time, etc. Surprisingly, the fundamental idea behind it all has not changed much: A user at Computer A wants to view a webpage at Computer B. Computer A informs Computer B of this fact, and Computer B sends the file over. The entire Internet is just that, a lot of computers sending files to each other.

In the scenario above, Computer A is what we call a client and Computer B is what we call a server. Computer A could also be a server to other computers, or, if Computer B wanted some data from Computer A, Computer A could even be a server for Computer B. As you know, it's really the process on the computer that is serving as a client or a server.


Overview

Why are we bothering you with this inane (and highly incomplete) history? Because we want you to write a web server. Web servers sit out there waiting for someone to ask for a file, and then they happily send it along. Pretty straightforward, right? The concept is simple, but the implementation is a little bit messier for two reasons.

You need to conform to the HTTP protocol. You can't just send data willy-nilly. There is a specific format for telling a client what you are about to send and then sending it.
You have to use socket programming to send the data. It's not much worse than low-level file I/O. The main difference is that more can go wrong when you're sending data across the network instead of writing it to a file.

Implementation Details

You should submit one or more .c and .h files and a makefile that will compile them into an executable called server. Here's an outline of the operations your code should perform.

Read in the command line arguments. If you don't have exactly three, quit with the following message.
Usage: ./server <port> <path to root>
Use the first command line argument as the port number. If it's a bad port number quit with the following message.
Bad port: port
Use the chdir() function to change the working directory to the directory specified. If the function returns an error, quit with the following message.
Could not change to directory: directory
Get a socket, bind it to the specified port, and then listen to it. You may need to use the setsockopt() function to make the socket reusable for multiple connections.
Try to accept a connection on the port you're listening to.
When you successfully accept a connection, process the request.
If it isn't a GET or HEAD request, ignore it.
If it is a GET or HEAD request:
First, if the file path ends with a slash (/), then concatenate index.html onto the path.
Next, if the file path starts with a slash (/), you'll need to skip it, since a path that starts with a slash specifies an absolute path.
If the file the client wants is available, send the appropriate information.
If the file is not available, send a 404 message.
Close the connection when you are done with it.
Go back to Step 5 and keep trying to accept more connections.

Extension	Type

html	text/html
htm	text/html
jpg	image/jpeg
jpeg	image/jpeg
gif	image/gif
png	image/png
txt	text/plain
c	text/plain
h	text/plain
pdf	application/pdf

You must support the following features.

GET
Content-Type for a large variety of common file types, often called MIME types. The table to the right is the minimum list you must support.
Content-Length, which will require you to determine the length of a file, either directly or by using something in the stat() and fstat() family of functions
HEAD
404 errors for non-existent files, composed of both of a 404 message and an appropriate HTML file
Command line options for the server to specify port and root directory
Compatibility with Mozilla Firefox

References

In order to help you write a standards-compliant web server, you'll need to consult some references. When doing so, it is important to read smart. References are extremely dull. You need to skim them to figure out the structure of the documents. Then, you need to focus in on just the stuff you need. If you try to read the entire thing (especially in the case of RFC1945), your head will explode. Note that you only need to support HTTP 1.0.

Here is a list of references we suggest you start with.

Beej's Guide to Network Programming
An excellent guide to basic network programming in C. You can go far with the notes, but you'll probably end up supplementing your work with code from here.

HTTP Made Really Easy
A very well put together guide to understanding the HTTP protocol. You do not need to worry about HTTP/1.1 for this project. Concentrate on the HTTP/1.0 section, and remember to read smart.

RFC1945 - Hypertext Transfer Protocol -- HTTP/1.0
An RFC (Request For Comments) is a document that specifies a standard or protocol so it can be followed by various vendors. RFC1945 is for HTTP/1.0, and should provide you with more than enough information to understand the protocol. This is the source for any picky little details.


Details

Unlike many assignments in this class, the standard libraries are completely available to you. Since this is a real program, we want you to have full access to all the tools you might use on the job.

Here are a few standard library functions you might find useful.

memcopy() - Copies one chunk of memory into another
memset() - Sets a chunk of memory to a particular value
sscanf() - String version of scanf() that can read whitespace delimited tokens from a string
strchr() and strrchr() - Find a char value in a string, starting at the front or the back
You will also need a number of networking functions to do the communication. At the very least, you will probably use the functions below.

socket() - Get a socket descriptor
bind() - Bind a port to a socket
listen() - Get a socket ready to accept incoming connections
accept() - Try to accept an incoming connection (if one is present)
recv() - Receive a stream of bytes
send() - Send a stream of bytes
setsockopt() - Set options on a socket (particularly whether or not a port is reusable)
There are a few other odd things flying around. For example, note that messages in HTTP end in CR-LF (\r\n), like lines of text in DOS files. Also, you need to pick a port to run your server on. A random number between 20000 and 30000 is a good idea. You should allow the port of your server to be specified at the command line when you start your server up.

Also, network byte order is not always the same as host byte order (the byte order of your machine). This will vary depending on whether you are on a Little Endian or a Big Endian architecture. In order to be sure that the byte orders of a few things are consistent (things like fields inside of the structures that specify network parameters, not things like the data that is actually sent), there are a few functions which can be used to convert between host and network byte orders. If you use these at all, it will only be in one or two places, but it is still a good idea for you to be familiar with them.

htonl() - Convert a 32-bit integer from host byte order to network byte order
htons() - Convert a 16-bit integer from host byte order to network byte order
ntohl() - Convert a 32-bit integer from network byte order to host byte order
ntohs() - Convert a 16-bit integer from network byte order to host byte order

Testing by Hand

A good way to learn the HTTP protocol is to talk to a server manually. A simple program called nc (or netcat, they're the same program) allows you to start doing this. nc will open up a port and let you type data directly into it. Doing so can let you see both sides of the HTTP communication (client and server).

nc as a client

First, let's use nc to connect to a pre-existing server and manually send a request. From reading the above resources, we know that a valid way to request the root document is as follows.

GET / HTTP/1.0
<hit enter again>
Let's use nc to do this. Fire up nc and have it connect to a web server (say, google.com) on port 80 as follows.

nc google.com 80
So, if you run that command, and then enter the HTTP request from above, it should look like the following. The command and user input is given in green

nc google.com 80
GET / HTTP/1.0
			
HTTP/1.0 200 OK
Date: Thu, 18 Apr 2014 17:16:55 GMT
Expires: -1
Cache-Control: private, max-age=0
Content-Type: text/html; charset=ISO-8859-1
Set-Cookie: PREF=ID=fde1ef9d7532d32d:FF=0:TM=1366305415:LM=1366305415:S=m8C7mvDa0KCfqYOK; expires=Sat, 18-Apr-2015 17:16:55 GMT; path=/; domain=.google.com
Set-Cookie: NID=67=mVjnX4KiYll7GcDvUbIsur2kVgn1YhhdRIQzBKDjHrEUUP3vR4VO5g6VcnLj9jdZFEl28bakPSK0aLR-8X6IALCwnVYt6_3CHjj9zA33wwMJjRgg7S9GaSWuBIeBQnk1; expires=Fri, 18-Oct-2014 17:16:55 GMT; path=/; domain=.google.com; HttpOnly
P3P: CP="This is not a P3P policy! See http://www.google.com/support/accounts/bin/answer.py?hl=en&answer=151657 for more info."
Server: gws
X-XSS-Protection: 1; mode=block
X-Frame-Options: SAMEORIGIN

<!doctype html><html itemscope="itemscope" itemtype="http://schema.org/WebPage"><head><meta content="Search the world's information, including webpages, images, videos and more. Google has many special features to help you find exactly what you're looking for." name="description"><meta content="noodp" name="robots"><meta itemprop="image" content="/images/google_favicon_128.png"><title>Google</title><script>(function(){
window.google={kEI:"hypwUbWkHI-ZlQWzsYDIDw",getEI:function(a){for(var b;a&&(!a.getAttribute||!(b=a.getAttribute("eid")));)a=a.parentNode;return b||google.kEI},https:function(){return"https:"==window.location.protocol},kEXPI:
...
There's a lot more junk after that, but it's critical that the server first sends a message saying HTTP/1.0 200 OK to indicate that it is going to send the file. What does it send if the file didn't exist? Give that a try on your own. It also sends lots of other information, and you don't have to include all of it. Regardless, you have a start for your server.

nc as a Server

There is another important question: What does Firefox send to the server? This data is what your server is going to have to parse. You can find out by putting nc into listen mode like so (using port 27809 as an arbitrary choice).

nc -l 27809
Now, if you tell your web browser to connect to that server and port (for example, http://127.0.0.1:27809/), nc will dump out exactly what the browser sends it. It will probably look something like the following. Again, the command is printed in green. Everything else is the message sent from the browser.

nc -l 27809
GET / HTTP/1.1
Host: 127.0.0.1:27809
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:18.0) Gecko/20100101 Firefox/
18.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Testing with a Browser

We suggest that you test using Mozilla Firefox. Theoretically, any browser should work if you get your server right.

Let's imagine that your server is running and is attached to port 27809 and you want to get file joe.html from it. Enter the following into the address bar in Firefox: http://127.0.0.1:27809/joe.html.

Provided Files

server.exe - Sample executable
index.html - A sample HTML document (right-click to save)
amy.jpg - An image referenced in the sample HTML document
Turn In

If everything is working correctly, the J: drive is mounted in Linux under /mnt/classes. Go to the class directory (J:\FA2014-2015\CS222A or J:\FA2014-2015\CS222B) there and create a directory called Project6.

Copy the contents of your project directory, including the makefile, the source C files, and header files into the directory you just created. Do not include any object files or executables. Running the make command must compile all the required C source code files and generate an executable named server.

The directory and file name must match exactly or you will risk scoring 0 points. Match even the spacing and capitalization specified. Automated tools are used to collect your files for grading.

All work must be submitted before Friday, May 1, 2015 at 11:59pm unless you are going to use a grace day.

Grading

Your grade will be determined by the following categories.

Category	Weight
GET Functionality	30%
HEAD Functionality	20%
Content-Type (MIME) support	10%
Content-Length	10%
404 Error Support	15%
Correct Makefile and File Naming	5%
Programming Style	10%
Under no circumstances should any member of one team look at the code written by another team. Tools will be used to detect code similarity automatically.

Code that does not compile will automatically score zero points.