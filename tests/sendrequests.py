import requests
import threading
import time

port = 8080

lchost = "http://127.0.0.1:" + str(port)

obj = {"hello": 1, "byte": 3}

def send_request():
    for i in range(0, 100):
        resp = requests.get(lchost)
        if resp.text == "<h1>Hello, World!<h1>":
            print("success")

        else:
            print("failure")


def create_threads():
    threads = []

    for _ in range(0, 1000):
        thread = threading.Thread(target=send_request)
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()


start_time = time.time()
create_threads()
print(time.time() - start_time)
