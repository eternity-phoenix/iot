#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from . import db


class Sensor(db.Model):
    __tablename__ = 'sensor'

    id = db.Column(db.String(50), index=True, nullable=False, unique=True, primary_key=True)
    name = db.Column(db.String(50), nullable=False, index=True)
    created_at = db.Column(db.DateTime, nullable=False)
    user_id = db.Column(db.ForeignKey('user.id'), nullable=False, index=True)

    datas = db.relationship(
        "Data",
        lazy="dynamic",
        backref="sensor"
    )

    def export_data(self):
        return {
            "id": self.id,
            "name": self.name,
            "create_at": self.created_at,
            "user_id": self.user_id,
        }
