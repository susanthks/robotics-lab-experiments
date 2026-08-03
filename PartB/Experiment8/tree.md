```bash
ros2_ws/
└── src/
    └── communication_demo/
        ├── communication_demo/
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
        'publisher = communication_demo.publisher:main',
        'subscriber = communication_demo.subscriber:main',
        'service = communication_demo.service:main',
        'client = communication_demo.client:main',
    ],
},
```
