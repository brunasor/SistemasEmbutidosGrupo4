#!/usr/bin/env python3

from http.server import BaseHTTPRequestHandler, HTTPServer
import logging
import serial
import json


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
        sendCommand(json.loads(direction))
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
    dir = direction["direction"]
    vel = direction["velocity"]
    if(dir=='UP'):
            print("Forward")
            ser.write(bytes("F:"+vel, 'utf-8'))
            return
    if(dir=='DOWN'):
            print("Backwards")
            ser.write(bytes("B:"+vel, 'utf-8'))
            return
    if(dir=='LEFT'):
            print("Left")
            ser.write(bytes("L:"+vel, 'utf-8'))
            return
    if(dir== 'RIGHT'):
            print("Right")
            ser.write(bytes("R:"+vel, 'utf-8'))   
            return      
    if(dir== 'DR'):
            print("DR")
            ser.write(bytes("D:"+vel, 'utf-8'))   
            return 
    if(dir== 'DL'):
            print("DL")
            ser.write(bytes("P:"+vel))   
            return 
    if(dir== 'HORN'):
            print("HORN")
            ser.write(b"A")   
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
