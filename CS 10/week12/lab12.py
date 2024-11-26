class computer:
    def __init__(self, processor, ram):
        # creating an instance variable name processor
        # and assigning it the value of the parameter named processor
        self.processor = processor
        
        # create an instance variable named ram
        # and assign it the value of the parameter named ram
        self.ram = ram
        # DO SOMETHING HERE


    # defining a setter for the processor instance variable
    def set_processor(self, processor):
        self.processor = processor

    # define a setter for the ram instance variable
    # DO SOMETHING HERE

    def set_ram(self, ram):
        self.ram = ram

    # defining a getter for the processor instance variable
    def get_processor(self):
        return self.processor

    # define a getter for the ram instance variable
    # DO SOMETHING HERE
    def get_ram(self):
        return self.ram

# Construct a computer object
# DO SOMETHING HERE

cm = computer("i5", "16GB")

print(cm.get_ram())
print(cm.get_processor())
# Use getters to display the processor and ram for the computer you constructed
# DO SOMETHING HERE

    