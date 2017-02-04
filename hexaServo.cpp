#include "hexaServo.h"

Adafruit_PWMServoDriver g_pwm = Adafruit_PWMServoDriver();

int hexaServoMap( int index )
{
  switch( index )
  {
    case 0:
      return _SERVO0_;
    case 1:
	    return _SERVO1_;
    case 2:
	    return _SERVO2_;
    case 3:
	    return _SERVO3_;
    case 4:
	    return _SERVO4_;
    case 5:
	    return _SERVO5_;
    case 6:
	    return _SERVO6_;
    case 7:
	    return _SERVO7_;
    case 8:
	    return _SERVO8_;
    case 9:
	    return _SERVO9_;
    case 10:
      return _SERVO10_;
    case 11:
	    return _SERVO11_;
  }
}

int hexaServoHome( int index )
{
  switch( index )
  {
    case 0:
      return _SERVOHOME0_;
    case 1:
	    return _SERVOHOME1_;
    case 2:
	    return _SERVOHOME2_;
    case 3:
	    return _SERVOHOME3_;
    case 4:
	    return _SERVOHOME4_;
    case 5:
	    return _SERVOHOME5_;
    case 6:
	    return _SERVOHOME6_;
    case 7:
	    return _SERVOHOME7_;
    case 8:
	    return _SERVOHOME8_;
    case 9:
	    return _SERVOHOME9_;
    case 10:
	    return _SERVOHOME10_;
    case 11:
	    return _SERVOHOME11_;
  }
}

void hexaServoInit()
{
  g_pwm.begin();
  g_pwm.setPWMFreq( _PWMFREQ_ );
}

void hexaHoming()
{
  int i;

  g_pwm.setPWM( hexaServoMap( 1 ), 0, hexaServoHome( 1 ) );
  g_pwm.setPWM( hexaServoMap( 3 ), 0, hexaServoHome( 3 ) );

  for( i = 0; i < 12; i++ )
  {
	  g_pwm.setPWM( hexaServoMap( i ), 0, hexaServoHome( i ) );
  }
}

void hexaShuttingDown()
{
  hexaHoming();
  /* to be done */
  delay(1000);
}

void hexaSetPos( int index, int pos )
{
  if( 6 > index )
  {
    g_pwm.setPWM( hexaServoMap( index ), 0, hexaServoHome( index ) + pos );
    Serial.print( "Servo " );
    Serial.print( index );
    Serial.print( " | Position: " );
    Serial.print( hexaServoHome( index ) );
    Serial.print( "+" );
    Serial.println( pos );

  }
  else
  {
    g_pwm.setPWM( hexaServoMap( index ), 0, hexaServoHome( index ) - pos );
    Serial.print( "Servo " );
    Serial.print( index );
    Serial.print( " | Position: " );
    Serial.print( hexaServoHome( index ) );
    Serial.print( "-" );
    Serial.println( pos );
  }
  delay(10);
}

void hexaToward( double lenght, double stepSize, int height )
{
  int i, hexaFor, hexaBack, corrHeight;
  double distance, corrStep;

  if( 0 > lenght )
  {
    distance = -lenght;
    hexaFor = _PWMHMIN_;
    hexaBack = _PWMHMAX_;
  }
  else
  {
    distance = lenght;
    hexaFor = _PWMHMAX_;
    hexaBack = _PWMHMIN_;
  }

  if( 0 > stepSize )
  {
    corrStep = 0;
  }
  else if( 1 < stepSize )
  {
    corrStep = 1;
  }
  else
  {
    corrStep = stepSize;
  }

  if( _PWMVMIN_ + _STDHEIGHT_ > height )
  {
    corrHeight = _PWMVMIN_ + _STDHEIGHT_;
  }
  else if( _PWMVMAX_ < height )
  {
    corrHeight = _PWMVMAX_;
  }
  else
  {
    corrHeight = height;
  }

  while( _ERRLENGHT_ * _STEPLENGHT_ < distance )
  {
    if( _STEPLENGHT_ * corrStep > distance )
    {
      corrStep = distance / _STEPLENGHT_;
    }
    distance -= _STEPLENGHT_ * corrStep;

    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 1, int( hexaFor * corrStep ) );
      hexaSetPos( 4 * i + 3, int( hexaBack * corrStep ) );
    }
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i, corrHeight );
    }
    delay( _STDBREAK_ );

    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 1, int( hexaBack * corrStep ) );
      hexaSetPos( 4 * i + 3, int( hexaFor * corrStep ) );
    }
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight );
    }
    delay( _STDBREAK_ );
  }
}

void hexaRotate( double angle, double stepSize, int height )
{
  int i, hexaFor, hexaBack, corrHeight;
  double absAngle, corrStep;

  if( 0 > angle )
  {
    absAngle = -angle;
    hexaFor = _PWMHMIN_;
    hexaBack = _PWMHMAX_;
  }
  else
  {
    absAngle = angle;
    hexaFor = _PWMHMAX_;
    hexaBack = _PWMHMIN_;
  }

  if( 0 > stepSize )
  {
    corrStep = 0;
  }
  else if( 1 < stepSize )
  {
    corrStep = 1;
  }
  else
  {
    corrStep = stepSize;
  }

  if( _PWMVMIN_ + _STDHEIGHT_ > height )
  {
    corrHeight = _PWMVMIN_ + _STDHEIGHT_;
  }
  else if( _PWMVMAX_ < height )
  {
    corrHeight = _PWMVMAX_;
  }
  else
  {
    corrHeight = height;
  }

  while( _ERRANGLE_ * _STEPANGLE_ < absAngle )
  {
    if( _STEPANGLE_ * corrStep > absAngle )
    {
      corrStep = absAngle / _STEPANGLE_;
    }
    absAngle -= _STEPANGLE_ * corrStep;
    
    for( i = 0; i < 3; i++)
    {
      hexaSetPos( 4 * i, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    hexaSetPos( 1, hexaBack * corrStep );
    hexaSetPos( 3, hexaFor * corrStep );
    hexaSetPos( 5, hexaBack * corrStep );
    hexaSetPos( 7, hexaBack * corrStep );
    hexaSetPos( 9, hexaFor * corrStep );
    hexaSetPos( 11, hexaBack * corrStep );
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i, corrHeight );
    }
    delay( _STDBREAK_ );

    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    hexaSetPos( 1, hexaFor * corrStep );
    hexaSetPos( 3, hexaBack * corrStep );
    hexaSetPos( 5, hexaFor * corrStep );
    hexaSetPos( 7, hexaFor * corrStep );
    hexaSetPos( 9, hexaBack * corrStep );
    hexaSetPos( 11, hexaFor * corrStep );
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight );
    }
    delay( _STDBREAK_ );
  }
}

void hexaMove( double lenght, double curve, double stepSize, int height )
{
  int i, hexaFor, hexaBack, corrHeight;
  double distance, corrStep, curveLeft, curveRight;

  if( 0 > lenght )
  {
    distance = -lenght;
    hexaFor = _PWMHMIN_;
    hexaBack = _PWMHMAX_;
  }
  else
  {
    distance = lenght;
    hexaFor = _PWMHMAX_;
    hexaBack = _PWMHMIN_;
  }

  if( -1 > curve )
  {
    curveLeft = 0;
    curveRight = 1;
  }
  else if( 0 > curve )
  {
    curveLeft = 0;
    curveRight = -curve;
  }
  else if( 1 > curve )
  {
    curveLeft = curve;
    curveRight = 0;
  }
  else
  {
    curveLeft = 1;
    curveRight = 0;
  }

  if( 0 > stepSize )
  {
    corrStep = 0;
  }
  else if( 1 < stepSize )
  {
    corrStep = 1;
  }
  else
  {
    corrStep = stepSize;
  }

  if( _PWMVMIN_ + _STDHEIGHT_ > height )
  {
    corrHeight = _PWMVMIN_ + _STDHEIGHT_;
  }
  else if( _PWMVMAX_ < height )
  {
    corrHeight = _PWMVMAX_;
  }
  else
  {
    corrHeight = height;
  }

  while( _ERRLENGHT_ * _STEPLENGHT_ < distance )
  {
    if( _STEPLENGHT_ * corrStep > distance )
    {
      corrStep = distance / _STEPLENGHT_;
    }
    distance -= _STEPLENGHT_ * corrStep;
    
    for( i = 0; i < 3; i++)
    {
      hexaSetPos( 4 * i, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    hexaSetPos( 1, hexaBack * corrStep * curveLeft );
    hexaSetPos( 3, hexaFor * corrStep * curveLeft );
    hexaSetPos( 5, hexaBack * corrStep * curveLeft );
    hexaSetPos( 7, hexaFor * corrStep * curveRight );
    hexaSetPos( 9, hexaBack * corrStep * curveRight );
    hexaSetPos( 11, hexaFor * corrStep * curveRight );
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i, corrHeight );
    }
    delay( _STDBREAK_ );

    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight - _STDHEIGHT_ );
    }
    delay( _STDBREAK_ );
    hexaSetPos( 1, hexaFor * corrStep * curveLeft );
    hexaSetPos( 3, hexaBack * corrStep * curveLeft );
    hexaSetPos( 5, hexaFor * corrStep * curveLeft );
    hexaSetPos( 7, hexaBack * corrStep * curveRight );
    hexaSetPos( 9, hexaFor * corrStep * curveRight );
    hexaSetPos( 11, hexaBack * corrStep * curveRight );
    delay( _STDBREAK_ );
    for( i = 0; i < 3; i++ )
    {
      hexaSetPos( 4 * i + 2, corrHeight );
    }
    delay( _STDBREAK_ );
  }
}
