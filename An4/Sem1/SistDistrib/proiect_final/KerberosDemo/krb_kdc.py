import hmac
import hashlib
import time

class KrbKDC:
    def __init__(self):
        self.users = {}

    def register_user(self, user):
        self.users[user.username] = user

    def issue_ticket(self, username, service_name):
        user = self.users.get(username)
        if user:
            timestamp = int(time.time())
            ticket = {
                "username": user.username,
                "timestamp": timestamp,
                "service": service_name,
                "shared_key": hmac.new(user.password.encode(), digestmod=hashlib.sha256).hexdigest()
            }
            user.tickets[service_name] = ticket
            return ticket
        else:
            return None

    def validate_ticket(self, ticket):
        user = self.users.get(ticket["username"])
        if user and user.tickets.get(ticket["service"]) == ticket:
            return True
        else:
            return False