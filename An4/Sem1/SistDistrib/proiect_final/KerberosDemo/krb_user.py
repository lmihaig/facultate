class KrbUser:
    def __init__(self, username, password):
        self.username = username
        self.password = password
        self.tickets = {}

    def get_ticket(self, kdc, service_name):
        ticket = kdc.issue_ticket(self.username, service_name)
        print("Ticket {} issued for {} to access {}".format(ticket, self.username, service_name))
        if ticket:
            self.tickets[service_name] = ticket
        return ticket