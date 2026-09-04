```bash
ros2_ws/
└── src/
    └── pub_sub_py/
        ├── pub_sub_py/
        │   ├── __init__.py
        │   ├── publisher.py
        │   ├── subscriber.py
        │   ├── service.py
        │   └── client.py
        ├── package.xml
        ├── setup.py
        └── setup.cfg

```

---

## Update Setup File setup.py

```python
entry_points={
    'console_scripts': [
        'publisher = pub_sub_py.publisher:main',
        'subscriber = pub_sub_py.subscriber:main',
        'service = pub_sub_py.service:main',
        'client = pub_sub_py.client:main',
    ],
},
```
