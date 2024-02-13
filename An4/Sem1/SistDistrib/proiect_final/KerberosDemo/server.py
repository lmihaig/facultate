from flask import Flask, request, jsonify
from krb_service import PrintService, EchoService
from krb_user import KrbUser
from krb_kdc import KrbKDC

app = Flask(__name__)


kdc = KrbKDC()
print_service = PrintService("PrintService", kdc)
echo_service = EchoService("EchoService", kdc)

@app.route('/register', methods=['POST'])
def register():
    username = request.json.get('username')
    password = request.json.get('password')
    user = KrbUser(username, password)
    kdc.register_user(user)
    return jsonify({'message': 'User registered successfully'}), 200

@app.route('/issue_ticket', methods=['POST'])
def issue_ticket():
    username = request.json.get('username')
    service_name = request.json.get('service_name')
    user = kdc.users.get(username)
    if not user:
        return jsonify({'message': 'User not found'}), 404
    if service_name not in ['PrintService', 'EchoService']:
        return jsonify({'message': 'Service not found'}), 404
    ticket = user.get_ticket(kdc, service_name)
    return jsonify({'ticket': ticket}), 200

@app.route('/request_service', methods=['POST'])
def request_service():
    username = request.json.get('username')
    service_name = request.json.get('service_name')
    user = kdc.users.get(username)
    if user and service_name in user.tickets:
        if service_name == "PrintService":
            response = print_service.request_service(user)
        elif service_name == "EchoService":
            response = echo_service.request_service(user)
        else:
            return jsonify({'message': 'Service not found'}), 404
        return jsonify({'response': response}), 200
    else:
        return jsonify({'message': 'User not found or no ticket for service'}), 404
    
@app.route('/user_exists/<username>', methods=['GET'])
def user_exists(username):
    exists = username in kdc.users
    return jsonify({'exists': exists})

if __name__ == "__main__":
    app.run(debug=True)