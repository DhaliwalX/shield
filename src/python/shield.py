import shield_cpp

shield_cpp.startWorkers()

def onNewConnection(connection):
    connection.print()


