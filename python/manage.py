__author__ = 'YiWei'

from flask.ext.migrate import Migrate, MigrateCommand
from flask.ext.script import Manager

from app import app
from app.models import *

migrate = Migrate(app, db)
manager = Manager(app)

manager.add_command('db', MigrateCommand)

if __name__ == '__main__':
    manager.run()
