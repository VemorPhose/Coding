from flask import Flask, send_from_directory

application = Flask(__name__, static_folder='.')

@application.route('/')
def serve_index():
    """Serves the index.html file from the root directory."""
    return send_from_directory('.', 'index.html')

if __name__ == '__main__':
    application.run(host='0.0.0.0', port=8080)
