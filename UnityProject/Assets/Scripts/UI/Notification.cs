using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

namespace WeDo2Sample
{
    public class Notification : TextUI
    {
        Image m_image;
        float m_defaultBgAlpha;
        float m_defaultTextAlpha;
        Coroutine m_coroutine;

        protected override void Awake()
        {
            tMPro = GetComponentInChildren<TextMeshProUGUI>();
            m_image = GetComponent<Image>();
            m_defaultBgAlpha = m_image.color.a;
            m_defaultTextAlpha = tMPro.alpha;
        }

        void Start()
        {
            gameObject.SetActive(false);
        }

        /// <summary>
        /// アルファ値を設定する.
        /// </summary>
        /// <param name="bgAlpha">背景のアルファ値.</param>
        /// <param name="textAlpha">テキストのアルファ値.</param>
        void SetAlpha(float bgAlpha, float textAlpha)
        {
            var bgColor = m_image.color;
            bgColor.a = bgAlpha;
            m_image.color = bgColor;
            tMPro.alpha = textAlpha;
        }

        /// <summary>
        /// 通知をフェードアウトさせる.
        /// </summary>
        /// <param name="frames">フェードアウトにかけるフレーム数.</param>
        /// <param name="delay">フェード開始までの時間（秒）.</param>
        /// <returns></returns>
        IEnumerator FadeOut(int frames, float delay)
        {
            SetAlpha(m_defaultBgAlpha, m_defaultTextAlpha);
            yield return new WaitForSecondsRealtime(delay);

            for (float i = 0; i < frames; i++)
            {
                float t = i / frames;
                SetAlpha(Mathf.Lerp(m_defaultBgAlpha, 0, t), Mathf.Lerp(m_defaultTextAlpha, 0, t));
                yield return null;
            }
            gameObject.SetActive(false);
        }

        /// <summary>
        /// 通知を表示する.
        /// </summary>
        /// <param name="message">通知するメッセージ.</param>
        public void Notify(string message)
        {
            if (m_coroutine != null)
            {
                StopCoroutine(m_coroutine);
            }
            Text = message;
            gameObject.SetActive(true);
            m_coroutine = StartCoroutine(FadeOut(50, 1));
        }
    }
}