#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from . import db


class User(db.Model):
    __tablename__ = 'user'

    id = db.Column(db.String(50), index=True, nullable=False, unique=True, primary_key=True)
    user_name = db.Column(db.String(50), nullable=False, index=True)
    created_at = db.Column(db.DateTime, nullable=False)
    password = db.Column(db.String(50), nullable=False)

    sensors = db.relationship(
        "Sensor",
        lazy="dynamic",
        backref="user"
    )

    def export_data(self):
        from flask.ext.sqlalchemy import sqlalchemy
        from .sensor import Sensor
        return {
            "id": self.id,
            "user_name": self.user_name,
            "create_at": self.created_at,
            "sensors": db.sesssion.Query(sqlalchemy.distinct(Sensor.name)).filter(User.id == Sensor.user_id).all(),
        }
