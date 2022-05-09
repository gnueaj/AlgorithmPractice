class Duck():
    def __init__(self, input_name):
        self.hidden_name = input_name
    def get_name(self):
        print('inside the getter')
        return self.hidden_name
    def set_name(self, input_name):
        print('inside the setter')
        self.hidden_name = input_name
        
don = Duck('Donald')
print(don.hidden_name)
don.hidden_name = 'Donna'
print(don.hidden_name)