#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from . import db


class Data(db.Model):
    __tablename__ = 'data'

    id = db.Column(db.Integer(), index=True, nullable=False, unique=True, primary_key=True)
    attribute = db.Column(db.String(50), nullable=False, index=True)
    created_at = db.Column(db.DateTime, nullable=False)
    value = db.Column(db.String(1000), nullable=False)
    unit = db.Column(db.String(50), nullable=False)
    sensor_id = db.Column(db.ForeignKey('sensor.id'), nullable=False, index=True)

    def export_data(self):
        return {
            "id": self.id,
            "attribute": self.attribute,
            "created_at": self.created_at,
            "value": self.value,
            "unit": self.unit,
            "sensor_id": self.sensor_id,
        }
