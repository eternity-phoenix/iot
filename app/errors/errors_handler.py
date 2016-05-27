#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from .. import app
from flask import jsonify, request


@app.errorhandler(ValueError)
def value_error_handler(ve):
    return jsonify({"status": 400, "msg": ve.args[0]}), 400
