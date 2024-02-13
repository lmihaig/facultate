class KrbService:
    def __init__(self, name, kdc):
        self.name = name
        self.kdc = kdc

    def request_service(self, user):
        ticket = user.tickets.get(self.name)
        if ticket and self.kdc.validate_ticket(ticket):
            return True
        else:
            return False

class PrintService(KrbService):
    def request_service(self, user):
        access_granted = super().request_service(user)
        if access_granted:
            print("Access granted to PrintService\n")
            return "Access granted to PrintService\nPrinting something here..."
        else:
            print("Access denied to PrintService\n")
            return "Access denied to PrintService\n"

class EchoService(KrbService):
    def request_service(self, user):
        access_granted = super().request_service(user)
        if access_granted:
            print("Access granted to EchoService\n")
            print("Echoing back your username: {}!\n".format(user.username))
            return "Access granted to EchoService\n" + "Echoing back your username: {}!\n".format(user.username)
        else:
            print("Access denied to EchoService\n")
            return "Access denied to EchoService\n"