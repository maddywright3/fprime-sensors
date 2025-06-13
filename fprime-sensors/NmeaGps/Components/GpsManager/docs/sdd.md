# NmeaGps::GpsManager

Converts GPS messages assembled by a FrameAssembler into GPS telemetry.

## Requirements

| Name | Description | Validation |
|---|---|---|
| NMEA-GPS-001 | The GpsManager shall read NMEA GPGGA messages | Unit-Test |
| NMEA-GPS-002 | The GpsManager shall telemeter GpsData        | Unit-Test |
| NMEA-GPS-003 | The GpsManager shall return incoming buffers  | Unit-Test |

## Port Descriptions
| Name | Description |
|---|---|
| dataIn | Incoming `Fw::Buffer` objects from frame accumulation |
| dataReturnOut | Return port for `Fw::Buffer` objects to frame accumulation |


## Events
| Name | Description |
|---|---|
| MalformedMessage | The incoming message was malformed |
| InvalidData      | The incoming message was well-formed and marked invalid |

## Telemetry
| Name | Description |
|---|---|
| Reading | GPS reading |

