package util

import (
	"time"

	"github.com/fatih/color"
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

func CustomLevelEncoder(isServer bool) zapcore.LevelEncoder {
    return func(level zapcore.Level, enc zapcore.PrimitiveArrayEncoder) {
        var levelStr string
        switch level {
        case zapcore.InfoLevel:
            if isServer {
                levelStr = color.GreenString("[INFO]")
            } else {
                levelStr = color.BlueString("[INFO]")
            }
        case zapcore.ErrorLevel:
            levelStr = color.RedString("[ERROR]")
        default:
            levelStr = level.CapitalString()
        }
        enc.AppendString(levelStr)
    }
}



func CustomTimeEncoder(t time.Time, enc zapcore.PrimitiveArrayEncoder) {
    enc.AppendString(t.Format("15:04:05"))
}

func InitLogger(isServer bool) *zap.Logger {
    config := zap.NewDevelopmentConfig()
    config.EncoderConfig.EncodeLevel = CustomLevelEncoder(isServer)
    config.EncoderConfig.EncodeTime = CustomTimeEncoder
    config.DisableCaller = true

    logger, err := config.Build()
    if err != nil {
        panic(err)
    }
    return logger
}
