#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

import flask
from flask.ext.sqlalchemy import SQLAlchemy

try:
    import pymysql
    pymysql.install_as_MySQLdb()
except:
    pass

db = SQLAlchemy()

app = flask.Flask(__name__)

app.config['SQLALCHEMY_DATABASE_URI'] = "mysql://root:password@localhost:3306/iot"
app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True
app.config['SQLALCHEMY_ECHO'] = True

db.init_app(app)

from .views import *
from .errors import *
