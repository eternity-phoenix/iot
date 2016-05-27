#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Etern'

from app import app

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
