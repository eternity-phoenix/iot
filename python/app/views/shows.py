#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from flask import render_template, jsonify, request

from app.models import *
from .. import app


@app.route('/show_datas/<user>/<sensor>/<attribute>/', methods=['GET'])
def get_shows(user, sensor, attribute):
    return render_template("show_datas.html")


@app.route('/show_datas/', methods=['POST'])
def get_shows_datas():
    try:
        user_id = request.json['user_id']
        sensor_id = request.json['sensor_id']
        attribute = request.json['attribute']
    except KeyError as e:
        raise ValueError('missing arg: %s' % e.args[0])

    data = Data.query.filter(Data.sensor_id == sensor_id, Data.attribute == attribute).order_by(Data.created_at.desc()).first()
    if not data:
        raise ValueError("no datas")
    return jsonify({"data": data.value})

