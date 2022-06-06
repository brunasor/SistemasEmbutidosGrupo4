#!/usr/bin/env python3
"""
Very simple HTTP server in python for logging requests
Usage::
    ./server.py [<port>]
"""
from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import serial


ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
ser.reset_input_buffer()
class S(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        logging.info("GET request,\nPath: %s\nHeaders:\n%s\n", str(self.path), str(self.headers))
        self._set_response()
        self.wfile.write("GET request for {}".format(self.path).encode('utf-8'))

    def do_POST(self):
        content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
        post_data = self.rfile.read(content_length) # <--- Gets the data itself
        direction  = (post_data.decode('utf-8'))
        sendCommand(direction)
        ##logging.info("POST request,\nPath: %s\nHeaders:\n%s\n\nBody:\n%s\n",str(self.path), str(self.headers), post_data.decode('utf-8'))
        self._set_response()
        self.wfile.write("POST request for {}".format(self.path).encode('utf-8'))

def run(server_class=HTTPServer, handler_class=S, port=8080):
    logging.basicConfig(level=logging.INFO)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    logging.info('Starting httpd...\n')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass6
    httpd.server_close()
    logging.info('Stopping httpd...\n')

def sendCommand(direction):
    print(direction)
    if(direction=='{"X":"0","Y":"1"}'):
            print("Forward")
            ser.write(b"F\n")
            return
    if(direction=='{"X":"0","Y":"-1"}'):
            print("Backwards")
            ser.write(b"B\n")
            return
    if(direction=='{"X":"-1","Y":"0"}'):
            print("Left")
            ser.write(b"L\n")
            return
    if(direction== '{"X":"1","Y":"0"}'):
            print("Right")
            ser.write(b"R\n")   
            return       
    else:
            print("Stoping")
            ser.write(b"b\n") 


if __name__ == '__main__':
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()


        