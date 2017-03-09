//
//  BDSSpeechSynthesizerDelegate.h
//  BDSSpeechSynthesizer
//
//  Created by  段弘 on 13-11-23.
//  Copyright (c) 2013年 百度. All rights reserved.
//

#import <Foundation/Foundation.h>
@class BDSSpeechSynthesizer;

typedef enum BDSAudioPlayerPauseSources
{
    BDS_AUDIO_PLAYER_PAUSE_SOURCE_USER,
    BDS_AUDIO_PLAYER_PAUSE_SOURCE_AUDIO_INTERRUPT,
    BDS_AUDIO_PLAYER_PAUSE_SOURCE_ENTERED_BACKGROUND
}BDSAudioPlayerPauseSources __attribute__((deprecated("This parameter will be removed from paused callback. Current implementation of synthesizerPaused is kept in for backward compatibility for now, but will always pass BDS_AUDIO_PLAYER_PAUSE_SOURCE_USER as source. Start using - (void)synthesizerdidPause; instead.")));


typedef enum BDSAudioFormat{
    BDS_AUDIO_FORMAT_PCM_8K = 0,
    BDS_AUDIO_FORMAT_PCM_16K = 1,
    BDS_AUDIO_FORMAT_MP3 = 2
}BDSAudioFormat;

@protocol BDSSpeechSynthesizerDelegate <NSObject>

/**
 * @brief 合成器开始工作
 *
 * @param speechSynthesizer 合成器对象
 */
@optional
/**
 * @brief Began synthesizing new sentence.
 *        Will receive one call for each queued sentence when SDK starts synthesizing them
 *
 * @param SynthesizeSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- and synthesizeSentence- interface.
 *
 *        SynthesizeSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerStartWorkingSentence:(NSInteger)SynthesizeSentence;

/**
 * @brief Finished synthesizing a sentence.
 *        Will receive one call for each queued sentence when SDK finishes synthesizing them
 *
 * @param SynthesizeSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- and synthesizeSentence- interface.
 *        
 *         SynthesizeSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerFinishWorkingSentence:(NSInteger)SynthesizeSentence;

/**
 * @brief Began speak a sentence.
 *        Will receive one call for each queued sentence when SDK begans playback on them
 *        Not called if only synthesizing
 *
 * @param SpeakSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- interface.
 *
 *        SpeakSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerSpeechStartSentence:(NSInteger)SpeakSentence;
/**
 * @brief 朗读完成
 *        Will receive one call for each queued sentence when SDK finishes playback on them
 *        Not called if only synthesizing
 *
 * @param SpeakSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- interface.
 *
 *        SpeakSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerSpeechEndSentence:(NSInteger)SpeakSentence;

/**
 * @brief 新的语音数据已经合成
 *
 * @param newData 语音数据
 * @param fmt Audio format in passed buffer.
 * @param newLength Currently synthesized character count of current sentence.
 *
 * @param SynthesizeSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- and synthesizeSentence- interface.
 *
 *        SynthesizeSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerNewDataArrived:(NSData *)newData
                       DataFormat:(BDSAudioFormat)fmt
                   characterCount:(int)newLength
                   sentenceNumber:(NSInteger)SynthesizeSentence;


/**
 * @brief Gives an estimation about how many characters have been spoken so far.
 *        Not called if only synthesizing
 *
 * @param newLength Currently finished speaking character count of current sentence.
 *
 * @param SpeakSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- interface.
 *
 *        SpeakSentence may be any value from NSInteger's value
 *        range, including negative values but excluding -1, which is reserved to
 *        indicate none/error.
 */
- (void)synthesizerTextSpeakLengthChanged:(int)newLength
                           sentenceNumber:(NSInteger)SpeakSentence;

/**
 * @brief invoked when player gets paused
 */
- (void)synthesizerdidPause;

- (void)synthesizerPaused:(BDSAudioPlayerPauseSources)src __attribute__((deprecated("src parameter will be removed from paused callback. Current implementation of synthesizerPaused is kept in for backward compatibility for now, but will always pass BDS_AUDIO_PLAYER_PAUSE_SOURCE_USER as pause source. Start using - (void)synthesizerdidPause; instead.")));

/**
 * @brief invoked when player is resumed from pause
 */
- (void)synthesizerResumed;

/**
 * @brief 合成器发生错误
 *
 * @param error 错误对象
 * @param SpeakSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- interface.
 *
 * @param SynthesizeSentence Sentence ID generated BY SDK and returned by
 *        speakSentence- and synthesizeSentence- interface.
 *
 *        SpeakSentence may be any value from NSInteger's value
 *        range, including negative values, also -1 may be encountered in this callback
 *        if error happened while only synthesizing or playback haven't started yet.
 *
 *        SynthesizeSentence may be any value from NSInteger's value
 *        range, including negative values, also -1 may be encountered in this callback
 *        if error happened in player and synthesizer had already finished it's work.
 */
- (void)synthesizerErrorOccurred:(NSError *)error
                        speaking:(NSInteger)SpeakSentence
                    synthesizing:(NSInteger)SynthesizeSentence;

@end
