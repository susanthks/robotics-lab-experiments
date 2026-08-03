#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


class AddTwoNumbersClient(Node):

    def __init__(self):

        super().__init__('add_two_numbers_client')

        self.client = self.create_client(
            AddTwoInts,
            'add_two_ints'
        )

        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Waiting for service...')

    def send_request(self, a, b):

        request = AddTwoInts.Request()

        request.a = a
        request.b = b

        future = self.client.call_async(request)

        rclpy.spin_until_future_complete(self, future)

        return future.result()


def main(args=None):

    rclpy.init(args=args)

    client = AddTwoNumbersClient()

    response = client.send_request(10, 20)

    client.get_logger().info(
        f'Result = {response.sum}'
    )

    client.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()
