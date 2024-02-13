import argparse
import requests

def register_user(username, password):
    response = requests.post('http://localhost:5000/register', json={'username': username, 'password': password})
    print(response.json()['message'])

def issue_ticket(username, service_name):
    response = requests.post('http://localhost:5000/issue_ticket', json={'username': username, 'service_name': service_name})
    if 'ticket' in response.json():
        print('Ticket received.')
    else:
        print(response.json()['message'])

def request_service(username, service_name):
    user_exists = requests.get(f'http://localhost:5000/user_exists/{username}')
    if not user_exists.json().get('exists'):
        print('User {} not found.'.format(username))
        return
    
    response = requests.post('http://localhost:5000/request_service', json={'username': username, 'service_name': service_name})
    if 'response' in response.json():
        print('Service response:', response.json()['response'])
        return

    # If the service request failed, try to issue a new ticket
    print('No valid ticket found. Requesting a new ticket...')
    issue_ticket(username, service_name)


    response = requests.post('http://localhost:5000/request_service', json={'username': username, 'service_name': service_name})
    if 'response' in response.json():
        print('Service response:', response.json()['response'])
    else:
        print(response.json()['message'])

parser = argparse.ArgumentParser(description='Kerberos CLI')
subparsers = parser.add_subparsers(dest='command')

register_parser = subparsers.add_parser('register')
register_parser.add_argument('username')
register_parser.add_argument('password')

issue_ticket_parser = subparsers.add_parser('issue_ticket')
issue_ticket_parser.add_argument('username')
issue_ticket_parser.add_argument('service_name')

request_service_parser = subparsers.add_parser('request_service')
request_service_parser.add_argument('username')
request_service_parser.add_argument('service_name')

args = parser.parse_args()

if args.command == 'register':
    register_user(args.username, args.password)
elif args.command == 'issue_ticket':
    issue_ticket(args.username, args.service_name)
elif args.command == 'request_service':
    request_service(args.username, args.service_name)